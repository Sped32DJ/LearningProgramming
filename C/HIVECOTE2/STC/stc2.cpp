#include <iostream>
#include <sys/types.h>
#include <vector>
#include <cmath>
#include <string>
#include <stdexcept>
#include <map>
#include <climits>
#include <iostream>
#include <random>
#include <optional>
#include <thread>

using namespace std;

// NOTE: May deprecate, Not too sure about below
typedef vector<vector<vector<float>>> TimeSeriesData; // 3D vector: [n_instances][n_dims][series_length]
struct Dataset{
  TimeSeriesData X;
  vector<int> y;
  int n_instances;
  int n_dims;
  int series_length;    // Takes a 3D tensor, returns a 2D matrix of primitive features
    vector<vector<double>> transform(
        const vector<vector<vector<double>>>& X
    );

  Dataset(const TimeSeriesData& data, vector<int> labels) : X(data), y(labels) {
    n_instances = data.size();
    n_dims = data[0].size();
    series_length = data[0][0].size();
  }
};

// Below doesn't do much
class BaseEstimator {
private:
  bool isFitted = false; // Flag to check if the estimator is fitted
protected:
  void setFitted() noexcept {
    isFitted = true;
  }
public:
//  BaseEstimator(const BaseEstimator&) = default;
//  BaseEstimator& operator=(const BaseEstimator&) = delete;
//  BaseEstimator() = default;
//  virtual ~BaseEstimator() = default;

};

class BaseTransformer : public BaseEstimator {
protected:
  virtual std::vector<std::string> ALLOWED_INPUT_SCITYPES() const {
    return {"DataObj"}; // Example allowed input scitypes
  }

  template<typename T>
  T getTag(const std::string& key) const;

  string detangleClassname() const noexcept {
    return "BaseTransformer"; // Return the class name
  }

public:
  vector<vector<double>> transform (vector<vector<double>>& X) {
    // Below are AI assumptions about the input data
    vector<vector<double>> X_inner; // Assuming X is a 2D vector of doubles
    vector<vector<double>> y_inner; // Placeholder for labels, if needed
    auto metadata_ = int(); // Placeholder for metadata, if needed
    bool return_metadata; // Flag to indicate if metadata should be returned
    vector<vector<double>> y; // FIX: Modify data type

    // Check if the transformer is fitted, else, throw an error
    // May not be required
    // checkIsFitted();


    // Input checking and conversion  for X/y,
    // checkX_Y(X, y, return_metadata);
    X_inner = X;
    y_inner = y;


    // Check if we need to vectorize
//    if(isVectorizeNeeded(X_inner)) {
//      X_inner = vectorize(X_inner);
//    }

    // if no vectorization is needed, call _transform directly
//    if(vectorizeNeeded(X_inner))
//      X_inner = _vectorize(X_inner);
//     else
    // TODO: Write _transform to handle the transformation logic
    // Check extension_templates/transformer.py for implementation
    X_inner = _transform(X_inner, y);


    // Obtain configs to control I/O control
    // TODO: write getConfig() to return a map of configs
    // Maybe I won't do this since there is a long level of abstraction
    map<string, string> configs = getConfig();
    string input_conv = configs["input_conversion"];
    string output_conv = configs["output_conversion"];

    vector<vector<double>> X_out;
    vector<vector<double>> Xt;

    // Converting output to mtype
    // TODO: Figure out how to implement _transform
    if(X.empty() || Xt.empty()) {
       X_out = Xt;
    } else if(input_conv == "on" &&
              output_conv == "on") {
     // X_out = _convertOutput(Xt,metadata_);
      X_out = Xt; // For now
    } else {
      X_out = Xt;
    }

    // Placeholder for transformation logic
    // This should return a transformed version of X
    return X_out; // Return an empty vector for now
  }

  vector<vector<double>> _transform(const vector<vector<double>>& X, const vector<vector<double>>&y) {
    // Placeholder for the actual transformation logic
    // This should be overridden by derived classes
    //    raise NotImplementedError("abstract method")
    return X; // For now, just return the input as output
  }

  map<string, string> getConfig() const {
    // NOTE: This is a placeholder; actual implementation will depend on the configuration structure
    return {{"input_conversion", "on"},
            {"output_conversion", "on"}};
  }


};

struct Tree {
  vector<double> thresholds;
  vector<int> featureIndices; // Indices of features used in the tree
  vector<int> childrenLeft;
  vector<int> childrenRight;
  vector<int> classVotes;

  Tree(const vector<int>& structure, const vector<double>& pcaMatrix)
    : thresholds(structure.size()), featureIndices(structure.size()), childrenLeft(structure.size()), childrenRight(structure.size()), classVotes(structure.size()) {
    // Initialize the tree structure based on the provided structure and PCA matrix
    // This is a placeholder; actual implementation will depend on the tree structure
  }

//  int wpredict(const vector<double>& features) const {
//    int node = 0;
//    while(childrenLeft[node] >= 0){
//      int f = featureIndices[node];
//      node = (features[f] <= thresholds[node]) ? childrenLeft[node] : childrenRight[node];
//    }
//    return classVotes[node]; // Return the class vote at the leaf node
//  }
};

// NOTE: This holds rng, part of predict
// All hardcoded for now
class RandomState {
  u_int64_t choice = 0x7F590B777640; // holds 12 hexadecimal digits = 48 bit value
  mt19937 seed; // print(rng) = RandomState(MT19937), not sure what this means
};

// Global function to check the random state
// TODO: Check this function, how would I really do this?
mt19937 checkRandomState(uint32_t seed) {
  if(!seed){
    return mt19937(random_device{}()); // Use a random device if seed is 0
  } else {
    return mt19937(seed); // Use the provided seed
  }
}

// NOTE: This holds predict
class RotationForest : public BaseEstimator {
public:
  int numTrees;
  vector<int> rotRows;
  vector<int> treeDimOffset;
  vector<vector<double>> rotationMatrices; // Rotation matrices for each tree
  vector<Tree> trees;
  //  RandomState rng; // Random state for reproducibility

  // TODO: Finish below
  vector<int> predict(const vector<vector<double>>& X) {
    // Check if the model is fitted (avoiding)
    // CheckIfitted(X) // We can skip this for now
    mt19937 rng = checkRandomState(random_state); // NOTE: We can skip the checks
    vector<vector<double>> probas = predict_proba(X); // Get the predicted probabilities

    vector<int> y_pred(X.size(), 0); // Initialize predictions

    for(const auto& prob : probas) {
      double max_prob = -1.0;
      vector<size_t> best_idxs;
      for(size_t i = 0;  i < prob.size(); ++i) {
        if(prob.at(i) == max_prob) {
          best_idxs.push_back(i); // Store indices of the maximum probabilities
        }
      }

      uniform_int_distribution<size_t> dist(0, best_idxs.size() - 1);
      int chosen = best_idxs[dist(rng)]; // Randomly choose one of the best indices
      //y_pred.push_back(classes_[chosen]); // Assign the chosen index to the prediction vector
      y_pred.push_back(chosen); // Assign the chosen index to the prediction vector
    }

    return y_pred; // Return the predicted classes
  }


  // FIX: May need to check this
  vector<vector<double>> predict_proba(const vector<vector<double>>& X) {
    size_t n_instances = X.size();
    size_t n_classes = classes_.size(); // classes_ is a forest, matrix of trees
    // class is a tree

    // Treat case of single class seen in fit
    if(n_instances == 1 ) {
      return vector<vector<double>>(n_classes, vector<double>(1, 1.0)); // Return a vector of zeros if n_instances is 1
    }
    vector<vector<double>> X_norm = normalizeAndTransform(X);

    vector<vector<double>> sum_proba(n_instances, vector<double>(n_classes, 0.0));

    for(int i = 0; i < n_estimators_; ++i){
      vector<vector<double>> prob = predict_proba_for_estimator(X_norm, i);
      for(size_t r = 0; r < n_instances; ++r) {
        for(size_t c = 0; c < n_classes; ++c) {
          sum_proba[r][c] += prob[r][c];
        }
      }
    }

    for(auto&row : sum_proba) {
      for(auto& val : row) {
        val /= static_cast<double>(n_estimators_); // Average the probabilities across all estimators
      }
    }
    return sum_proba; // Return the averaged probabilities
  }

  // (ndarray X, DecisionTreeClassifier clf, list pcas, list groups)
  // TODO: Build CLF class
  vector<vector<double>> predict_proba_for_estimator(vector<vector<double>> X, DecisionTreeClassifier clf, vector<double> pcas, vector<double> groups ){

  }

};

// NOTE: Probably already exists in HLS
vector<double> z_normalize_series(const vector<double>& series){
  double sum = 0.0;
  // compute mean
  for(double val : series) {
    sum += val;
  }

  double mean = sum / series.size();

  // Compute standard deviation
  double sq_sum = 0.0;
  for(double val : series) {
    sq_sum += (val - mean) * (val - mean);
  }
  double stddev = sqrt(sq_sum / series.size());

  // Normalize the series
  vector<double> arr(series.size());
  if(stddev > 0) {
    for(size_t i = 0; i < series.size(); ++i) {
      arr[i] = (series[i] - mean) / stddev;
    }
  } else {
    // If stddev is zero, fill with zeros
    fill(arr.begin(), arr.end(), 0.0);
  }

  return arr;
}

// From Fit()
//        self.shapelets = [
//            (
//                s[0],
//                s[1],
//                s[2],
//                s[3],
//                s[4],
//                self.classes_[s[5]],
//                z_normalise_series(X[s[4], s[3], s[2] : s[2] + s[1]]),
//            )
//            for class_shapelets in shapelets
//            for s in class_shapelets
//            if s[0] > 0
//        ]
//        NOTE: This is defined inside fit(), making self.classes_[s[5]], possible
struct Shapelet {
  int seriesID; // shapelet[0] = s[0]
  int startPos; // shapelet[1] = s[1]
  int length; // shapelet[2] = s[2]
  vector<double> values; // shapelet[3] = s[3], TODO: figure out the size of vector, at least the max
  int classLabel; // shapelet[4] = s[4]
  vector<double> classes;  // shapelet[5] = self.classes_[s[5]] NOTE: May actually be int
  // z_normalise_series(X[s[4], s[3], s[2] : s[2] + s[1]]) // shapelet[4]
  Shapelet(int seriesID, int startPos, int length, vector<double> values, int classLabel, vector<double> classes)
    : seriesID(seriesID), startPos(startPos), length(length), values(values), classLabel(classLabel), classes(classes) {}
};

// _online_shapelet_distance(series[shapelet[3]], shapelet[6], self._sorted_indices[n], shapelet[2], shapelet[1] )
// _online_shapelet_distance(series(shapelet.values), )
//
//     for i, series in enumerate(X):
//        if i != inst_idx:
//            distance = _online_shapelet_distance(
//                series[dim], shapelet, sorted_indices, position, length
//            )
//        else:
//            distance = 0
// TODO: Just make sure shapelet was correctly used
double _online_shapelet_distance(const vector<double>& series, const Shapelet& shapelet,
                                 vector<double>& sorted_indices, double& position, int& length) {
  vector<double> subseq;
  // Subseq = series[pos : pos+length]
  for(int i = position; i < position+length; ++i ){
    subseq.push_back(series.at(i));
  }

  double sum = 0.0;
  double sum2 = 0.0;

  for(double val : series) {
    sum += val;
    sum2 += val * val;
  }

  double mean = sum / length;
  double std = sqrt((sum2-mean*mean*length) / length);

  if(std > 0){
    // Z-score normalization
    // z = (X - mean) / std
    for(int i = 0; i < length; ++i) {
      subseq.at(i) = (subseq.at(i ) - mean) / std;
    }
  } else {
    // Fill subseq with 0s
    for(int i = 0; i < length; ++i){
      subseq.at(i) = 0;
    }
  }

  double best_dist = 0.0;
  // Fix this to where it works properly with shapelets
  for(int j = 0; j < length; ++j) {
    best_dist += pow(shapelet.values[j] - subseq[j] , 2);
  }

  int i = 1;
  vector<bool> traverse = {true, true};
  vector<double> sums = {sum, sum};
  vector<double> sums2 = {sum2, sum2};

  while (traverse[0] || traverse[1]){
    for (int n = 0 ; n < 2 ; ++n){
      int mod = (n == 0 ? -1 : 1);
      int pos = position + mod * i;
      traverse.at(n) = (n == 0 ? pos >= 0 : pos <= (int)series.size() - length);
      if(!traverse.at(n)) continue;

      double start = series.at(pos - n);
      double end = series.at(pos - n + length);

      sums.at(n) += mod*end - mod*start;
      sums2.at(n) += mod*end*end - mod*start*start;

      mean = sums.at(n) / length;
      std = sqrt((sums2.at(n) - mean*mean*length) / length);

      double dist = 0.0;
      double eps = 1e-8; // Numerical eps, to avoid division by zero
      bool use_std = (std > eps);

      for(int j = 0; j < length; ++j){
        double val = use_std ? (series.at(pos + sorted_indices.at(j)) - mean) / std :  0.0;
        double temp = shapelet.values.at(sorted_indices.at(j)) - val;
        dist += temp*temp;

        if(dist > best_dist) break;
      }

      best_dist = (dist > best_dist) ? dist : best_dist;
    }
    ++i;
  }
  //return best_dist / length;
  return 1 / length * best_dist;
}

class RandomShapeletTransform : BaseTransformer {
public:
    int n_shapelet_samples;
    int max_shapelets;
    int max_shapelet_length;
    int time_limit_in_minutes;
    int contract_max_n_shapelet_samples;
    int n_jobs;
    int batch_size;
    int random_state;
    vector<Shapelet> shapelets; // Vector to hold the shapelets

    RandomShapeletTransform(int n_shapelet_samples,
                            int max_shapelets,
                            int max_shapelet_length,
                            int time_limit_in_minutes,
                            int contract_max_n_shapelet_samples,
                            int n_jobs,
                            int batch_size,
                            int random_state) :
        n_shapelet_samples(n_shapelet_samples),
        max_shapelets(max_shapelets),
        max_shapelet_length(max_shapelet_length),
        time_limit_in_minutes(time_limit_in_minutes),
        contract_max_n_shapelet_samples(contract_max_n_shapelet_samples),
        n_jobs(n_jobs),
        batch_size(batch_size),
        random_state(random_state) {}

  vector<vector<double>> _transform(vector<vector<double>> X){
    if(shapelets.empty()) {
      throw runtime_error("Shapelets is an empty vector.");
    }
    // What ever this does, this is python
    // output[i][j] = distance(X[i], shapelets[j])
    vector<vector<double>> output(X.size(), shapelets.size(), 0.0);

    auto worker = [&](size_t start, size_t end) {
      for(size_t i = start; i < end; ++i) {
        for(size_t j = 0; j < shapelets.size(); ++j) {
          output[i][j] = computeDistance(X[i], shapelets[j]); // Placeholder for distance computation
        }
      }
    };

    if(n_jobs <= 1){
      worker(0, X.size());
    }else {
      vector<thread> threads;
      size_t batch_size = (X.size() + n_jobs - 1 )/ n_jobs;
      //size_t batch_size = (X.size()) / n_jobs;
      for(int i = 0; i < n_jobs; ++i) {
        size_t start = i * batch_size;
        //size_t end = (i == n_jobs - 1) ? X.size() : (i + 1) * batch_size;
        size_t end = min(start - batch_size, X.size());
        threads.emplace_back(worker, start, end);
      }
      for(auto& t : threads) {
        t.join();
      }
    }

  }
};

class ShapeletTransformClassifier : BaseTransformer {
public:
  // Parameters

  // TODO: What does it mean to be number of shaplet samples?
  int n_shaplet_samples; // default value: 10000
  int max_shaplets; // default value: None
  int max_shaplet_length; // default value: None
  // BaseEstimator estimator = 0; // default value: None
  int transform_limit_in_minutes; // default value: None
  int time_limit_in_minutes;
  int contract_max_n_shaplets; // default value: np.inf
  bool save_transformed_data; // default value: False
  int n_jobs; // default value: 1

  // NOTE: Is this the number of decision trees?
  int batch_size; // default value: 100
  int random_state ; // default value: 0  TODO: What are the states

  // Attributes
  // NOTE: Req for shapelets, not sure if vector<double>
  vector<double> classes_; // list of classifiers
  int n_classes_; // number of classes
  int fit_time_; // time taken to fit the model
  int n_instances_;
  int n_dims_;
  int series_length_;
  //list transformed_data_; // List of shape of ndarray
  RandomShapeletTransform _transformer;
  RotationForest _estimator; // Assuming RotationForest is a class that implements the classifier
  RandomState rng;

  int _predict(const vector<vector<double>>& X) {
    // Change type
//    int X_t = self._transform.transform(X).to_numpy()
//    return self._estimator.predict(X_t);
//    ShapeletTransformClassifier _transformer = ShapeletTransformClassifier();
    vector<vector<double>> Xt = _transformer.transform(X);
    return _estimator.predict(Xt);

  }
};

int main(){
  cout << "I love STC" << endl;
  return 0;
}

