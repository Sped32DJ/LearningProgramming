#include <climits>
#include <vector>
using namespace std;

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


};

