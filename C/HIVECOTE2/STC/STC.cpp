#include <climits>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <algorithm>

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
// vector<Shapelet> loadShapelets(const string& path);
// RotationForestModel loadRotationForestModel(const string& path);

// May need to depricate since not requried if we know
// our input if Fitted
class BaseEstimator {
protected:
  bool isFitted; // Flag to check if the estimator is fitted
public:
  BaseEstimator() : isFitted(false) {}

  bool checkIsFitted() const {
    return isFitted;
  }


  void checkIsFitted(const string& methodName = "") {
    if(!isFitted) {
      throw runtime_error("This " + methodName + " method can only be called after the model is fitted.");
    }
  }


};



class BaseTransformer : public BaseEstimator {
public:
  vector<vector<double>> transform(const vector<vector<double>>& X) {
    // Check if the transformer is fitted, else, throw an error
    checkIsFitted();

    // Input checking


    // Placeholder for transformation logic
    // This should return a transformed version of X
    return vector<vector<double>>(); // Return an empty vector for now
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

  int predict(const vector<double>& features) const {
    int node = 0;
    while(childrenLeft[node] >= 0){
      int f = featureIndices[node];
      node = (features[f] <= thresholds[node]) ? childrenLeft[node] : childrenRight[node];
    }
    return classVotes[node]; // Return the class vote at the leaf node
  }
};

struct RotationForestModel {
  int numTrees;
  vector<int> rotRows;
  vector<int> treeDimOffset;
  vector<vector<double>> rotationMatrices; // Rotation matrices for each tree
  vector<Tree> trees;

  int totalDims() const {
    int total = 0;
    for(int i = 0; i < numTrees; ++i) {
      total += rotRows[i];
    }
    return total;
  }

  // TODO: Lots of working required here
  vector<double> applyRotation(const vector<double>& x, const RotationForestModel& model){
    vector<double> rotated(model.totalDims(), 0.0);

    for(int i = 0; i < model.numTrees; ++i){
      int rows = model.rotRows[i];
      int cols = (int)x.size();
      const auto& mat = model.rotationMatrices[i];

      // Mult mat (rows x cols) with x (cols))
      for(int r = 0; r < rows; ++r){
        double sum = 0.0;
        int base = r * cols;
        for(int c = 0; c < cols; ++c){
          sum += mat[base + c] * x[c];
        }
        rotated[model.treeDimOffset[i] + r] = sum;
      }
    }
    return rotated;
  }

  // predictClass(x, model)
  int predictClass(const vector<double>& features, const RotationForestModel& model) {
    auto xr = applyRotation(features, model);
    std::map<int, int> classVotes; // Map to count votes for each class
    for(auto &tree : model.trees) {
      classVotes[tree.predict(xr)]++;
    }
    return std::max_element(classVotes.begin(), classVotes.end(),
                            [](const pair<int, int>& a, const pair<int, int>& b) {
                              return a.second < b.second;
                            })->first; // Return the class with the most votes

  }
  int predict(vector<double>& x) {
    // Check if the model is fitted
    if(!checkIsFitted()) {
      throw runtime_error("Model is not fitted yet.");
    }
    return predictClass(x, *this);
  }

//  vector<double> applyRotation(const vector<double>& data, const vector<vector<double>>& rotationMatrix) {
//    vector<double> transformedData(rotationMatrix.size(), 0.0);
//    for (size_t i = 0; i < rotationMatrix.size(); ++i) {
//      for (size_t j = 0; j < data.size(); ++j) {
//        transformedData[i] += rotationMatrix[i][j] * data[j];
//      }
//    }
//    return transformedData;
//  }

}



typedef vector<vector<vector<float>>> TimeSeriesData; // 3D vector: [n_instances][n_dims][series_length]

class Dataset{
public:
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

class ShapeletTransform {
public:

  int n_shaplet_samples;
  int max_shaplets;
  vector<Shapelet> selected_shapelets;

  ShapeletTransform(int n_shaplet_samples, int max_shaplets)
    : n_shaplet_samples(n_shaplet_samples), max_shaplets(max_shaplets) {}

  // Placeholder for shapelet extraction logic
  // This should populate selected_shapelets based on the dataset
  void fit(const Dataset& dataset);

  vector<vector<float>> transform(const Dataset& dataset);

  double euclideanDistance(const vector<double>& a, const vector<double>& b) {
    if (a.size() != b.size()) {
      throw runtime_error("Vectors must be of the same length for distance calculation.");
    }
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
      double diff = a[i] - b[i];
      sum += diff * diff;
    }
    return sqrt(sum);
  }

  // For each shapelet, compute the minimum distance on series
  vector<double> computeFeatures(const vector<float>& series, const vector<Shapelet>& shapelets) {
    vector<double> features;

    for(size_t i = 0; i < shapelets.size(); ++i) {
      const Shapelet& shapelet = shapelets[i];
      double best = numeric_limits<double>::max();

      for(size_t j = 0; j + shapelet.length <= series.size(); ++j) {
        // Extract the sub-series of the same length as the shapelet
        vector<double> subSeries(series.begin() + j, series.begin() + j + shapelet.length);
        // Compute the distance
        double dist = euclideanDistance(subSeries, shapelet.values);
        if (dist < best) {
          best = dist;
        }
      }
      // Filling in vector with the best distance found
      features.push_back(best);
    }

    return features;
  }

private:
  float shapeletDistance(const vector<float>& series, const Shapelet& shapelet);


};

class ShapeletTransformClassifier {
public:
  // Parameters

  // TODO: What does it mean to be number of shaplet samplse?
  int n_shaplet_samples = 10000; // default value: 10000
  int max_shaplets = INT_MAX; // default value: None
  int max_shaplet_length = INT_MAX; // default value: None
  // BaseEstimator estimator = 0; // default value: None
  int transform_limit_in_minutes = INT_MAX; // default value: None
  int time_limit_in_minutes = 0;
  int contract_max_n_shaplets = INT_MAX; // default value: np.inf
  bool save_transformed_data = false; // default value: False
  int n_jobs = 1; // default value: 1

  // NOTE: Is this the number of decision trees?
  int batch_size = 100; // default value: 100
  int random_state = 0; // default value: 0  TODO: What are the states

  // Attributes
  //list classes_; // list of classifiers
  int n_classes_; // number of classes
  int fit_time_; // time taken to fit the model
  int n_instances_;
  int n_dims_;
  int series_length_;
  //list transformed_data_; // List of shape of ndarray

  ShapeletTransformClassifier(int n_shaplet_samples, int max_shaplets, int max_shaplet_length,
                              int transform_limit_in_minutes, int time_limit_in_minutes,
                              int contract_max_n_sh) : n_shaplet_samples(n_shaplet_samples),
    max_shaplets(max_shaplets), max_shaplet_length(max_shaplet_length),
    transform_limit_in_minutes(transform_limit_in_minutes),
    time_limit_in_minutes(time_limit_in_minutes) {}

  ShapeletTransformClassifier() {
  int n_shaplet_samples = 10000; // default value: 10000
  int max_shaplets = 0; // default value: None
  int max_shaplet_length = 0; // default value: None
  // BaseEstimator estimator = 0; // default value: None
  int transform_limit_in_minutes = 0; // default value: None
  int time_limit_in_minutes = 0;
  int contract_max_n_shaplets = INT_MAX; // default value: np.inf
  bool save_transformed_data = false; // default value: False
  int n_jobs = 1; // default value: 1
  int batch_size = 100; // default value: 100
  int random_state = 0; // default value: NONE  TODO: What are the states
  }


  // fit (train portion)
  // For now, we will call the python code
  // to train the model, then C++ the inference portion
  void fit();

  // Focus on predict (inference) portion)
  // X: 3D np.array of shape = [n_instances, n_dimensions, series_length]
  //  the data to make predictions for./
  // Returns
  // y : array-like, shape = [n_instances]
  // Predicted class labels.
  // more like Vector predict(const Tensor3D& X)
  int predict(const Tensor3D& X) {
    // Change type
//    int X_t = self._transform.transform(X).to_numpy()
//    return self._estimator.predict(X_t);
    Shapelet Xt = BaseTransformer.transform(X);
    return BaseEstimator.predict(Xt);


  }

  void predict_proba();

  void getTrainProb();

  void getTestParams();


};

int main(int argc, char** argv){
  //vector<Shapelet> loadShapelets(const std::string &path);
  //RotationForestModel loadRotationForest(const std::string &path);
// RotationForestModel should include: PCA matrices & tree structures  auto shapelets = loadShapelets("shapelets.bin");
  auto model = loadRotationForest("rotForest.bin");

  vector<double> series = loadSeries("series.csv");
  auto feats = computeFeatures(series, shapelets);
  int cls = predictClass(feats, model);
  cout << "Predicted class: " << cls << endl;
  return 0;

}
