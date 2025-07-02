#include <climits>
using namespace std;

class ShapletTransformClassifier{
private:
  // Parameters
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
  int random_state = 0; // default value: 0  TODO: What are the states

  // Attributes
  //list classes_; // list of classifiers
  int n_classes_; // number of classes
  int fit_time_; // time taken to fit the model
  int n_instances_;
  int n_dims_;
  int series_length_;
  //list transformed_data_; // List of shape of ndarray





};

