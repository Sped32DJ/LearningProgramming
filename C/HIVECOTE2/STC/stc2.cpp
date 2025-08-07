#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <stdexcept>
#include <map>
#include <climits>

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

//  ShapeletTransformClassifier(int n_shapelet_samples = 10000,
//                             int max_shapelets = INT_MAX,
//                             int max_shapelet_length = INT_MAX,
//                             int transform_limit_in_minutes = INT_MAX,
//                             int time_limit_in_minutes = 0,
//                             int contract_max_n_shapelets = INT_MAX,
//                             bool save_transformed_data = false,
//                             int n_jobs = 1,
//                             int batch_size = 100,
//                             int random_state = 0) :
//    n_shaplet_samples(n_shapelet_samples),
//    max_shaplets(max_shapelets),
//    max_shaplet_length(max_shapelet_length),
//    transform_limit_in_minutes(transform_limit_in_minutes),
//    time_limit_in_minutes(time_limit_in_minutes),
//    contract_max_n_shaplets(contract_max_n_shapelets),
//    save_transformed_data(save_transformed_data),
//    n_jobs(n_jobs),
//    batch_size(batch_size) {}



  // Get clarification on the classes
  //        X : 3D np.array of shape = [n_instances, n_dimensions, series_length]
  //            The training data.
  //        y : array-like, shape = [n_instances]
  //            The class labels.
//..  ShapeletTransformClassifier(int n_shaplet_samples, int max_shaplets, int max_shaplet_length,
//..                              int transform_limit_in_minutes, int time_limit_in_minutes,
//..                              int contract_max_n_sh) : n_shaplet_samples(n_shaplet_samples),
//..    max_shaplets(max_shaplets), max_shaplet_length(max_shaplet_length),
//..    transform_limit_in_minutes(transform_limit_in_minutes),
//..    time_limit_in_minutes(time_limit_in_minutes) {}

//  ShapeletTransformClassifier() {
//  int n_shaplet_samples = 10000; // default value: 10000
//  int max_shaplets = 0; // default value: None
//  int max_shaplet_length = 0; // default value: None
//  // BaseEstimator estimator = 0; // default value: None
//  int transform_limit_in_minutes = 0; // default value: None
//  int time_limit_in_minutes = 0;
//  int contract_max_n_shaplets = INT_MAX; // default value: np.inf
//  bool save_transformed_data = false; // default value: False
//  int n_jobs = 1; // default value: 1
//  int batch_size = 100; // default value: 100
//  int random_state = 0; // default value: NONE  TODO: What are the states
//  }


  // fit (train portion)
  // For now, we will call the python code
  // to train the model, then C++ the inference portion
//  void fit(ShapeletTransformClassifier, vector<int> X, y){}

  // Focus on predict (inference) portion)
  // X: 3D np.array of shape = [n_instances, n_dimensions, series_length]
  //  the data to make predictions for./
  // Returns
  // y : array-like, shape = [n_instances]
  // Predicted class labels.
  // more like Vector predict(const Tensor3D& X)
//  int _predict(const Tensor3D& X) {
  int _predict(const vector<vector<double>>& X) {
    // Change type
//    int X_t = self._transform.transform(X).to_numpy()
//    return self._estimator.predict(X_t);
//    ShapeletTransformClassifier _transformer = ShapeletTransformClassifier();
    vector<vector<double>> Xt = _transformer.transform(X);
    return _estimator.predict(Xt);

  }

  // TODO: Finish below
  int predict(const vector<vector<double>>& X) {
    // Check if the model is fitted (avoiding)
    int rng = checkRandomState(this->random_state);
    return _predict(X);
  }

  // TODO: Finish below, start it from the bottom
  int checkRandomState(int random_state) {
    if(seed.isNone(random_state) || seed.isNPRand()) {
      random_state = 0; // Default value if None
    } else if(random_state < 0) {
      throw invalid_argument("Random state must be a non-negative integer.");
    }
    return random_state; // For now, just return the state
  }

  void predict_proba();

  void getTrainProb();

  void getTestParams();


};

