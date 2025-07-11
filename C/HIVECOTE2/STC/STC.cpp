#include <climits>
#include <vector>
using namespace std;

class Shapelet {
public:
  int dim;
  int start;
  int length;
  vector<float> values;
  float gain;
  Shapelet(int dim, int start, int length, vector<float> values, float gain)
    : dim(dim), start(start), length(length), values(values), gain(gain) {}
};

typedef vector<vector<vector<float>>> TimeSeriesData; // 3D vector: [n_instances][n_dims][series_length]

class Dataset{
public:
  TimeSeriesData X;
  vector<int> y;
  int n_instances;
  int n_dims;
  int series_length;

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

private:
  float shapeletDistance(const vector<float>& series, const Shapelet& shapelet);


};

class KNNClassifier {
public:
  int k;
  vector<vector<float>> x_data;
  vector<int> y_train;

  KNNClassifier(int k) : k(k) {}

  void fit(const vector<vector<float>>& X, const vector<int>& y) {
    x_data = X;
    y_train = y;
  }

  vector<int> predict(const vector<vector<float>>& X);
};



class ShapletTransformClassifier{
private:
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

  // May be redundant, but keeping it here
  void init(){
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

<<<<<<< HEAD
    // Then do all the implicit definitions
    // self.n_shaplet_samples = n_shaplet_samples
  }

// Get clarification on the classes
//        X : 3D np.array of shape = [n_instances, n_dimensions, series_length]
//            The training data.
//        y : array-like, shape = [n_instances]
//            The class labels.
  void fit(ShapletTransformClassifier, vector<int> X, y){

  }

  void predict(){
  }

  void predict_proba(){}

  void getTrainProbs(){}

  void getTestParams(){}
=======
  // Initializing all the parameters
  void init();

  void fit();

  void predict();

  void predict_proba();

  void getTrainProb();

  void getTestParams();
>>>>>>> refs/remotes/origin/main


};

