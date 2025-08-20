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

using namespace std;

struct Shapelet {
  int seriesID; // [0]
  int startPos; // [1]
  int length; // [2]
  vector<double> values; // [3]
  int classLabel; // [4]
  Shapelet(int seriesID, int startPos, int length, vector<double> values, int classLabel)
    : seriesID(seriesID), startPos(startPos), length(length), values(values), classLabel(classLabel) {}
};

// NOTE: May deprecate, because this is intense
struct Tensor3D {
  vector<vector<vector<double>>> data;
  int dim1, dim2, dim3;

  Tensor3D(int d1, int d2, int d3) : dim1(d1), dim2(d2), dim3(d3) {
    data.resize(d1, vector<vector<double>>(d2, vector<double>(d3)));
  }
};

// NOTE: May deprecate, Not too sure about below
typedef vector<vector<vector<float>>> TimeSeriesData; // 3D vector: [n_instances][n_dims][series_length]
struct Dataset{
  TimeSeriesData X;
  vector<int> y;
  int n_instances;
  int n_dims;
  int series_length;    // Takes a 3D tensor, returns a 2D matrix of primitive features
    std::vector<std::vector<double>> transform(
        const std::vector<std::vector<std::vector<double>>>& X
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
    mt19937 rng = checkRandomState(random_state_); // NOTE: We can skip the checks
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


  // May need to check this
  vector<vector<double>> predict_proba(const vector<vector<double>>& X) {
    size_t n_instances = X.size();
    size_t n_classes = classes_.size();

    if(n_instances == 1 ) {
      return vector<vector<double>>(n_classes, vector<double>(1, 1.0)); // Return a vector of zeros if n_instances is 1
    }
    vector<vector<double>> X_norm = normalizeAndTransform(X);

    vector<vector<double>> sum_proba(n_instances, vector<double>(n_classes, 0.0));

    for(int i = 0; i < n_estimators_; ++i){
      auto prob = predict_proba_for_estimator(X_norm, i);
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

};

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
};

class ShapeletTransformClassifier : BaseTransformer {
public:
  // Parameters

  // TODO: What does it mean to be number of shaplet samplse?
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
  //list classes_; // list of classifiers
  int n_classes_; // number of classes
  int fit_time_; // time taken to fit the model
  int n_instances_;
  int n_dims_;
  int series_length_;
  //list transformed_data_; // List of shape of ndarray
  //ShapeletTransformClassifier _transformer;
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

