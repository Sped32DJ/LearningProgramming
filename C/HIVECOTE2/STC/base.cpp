#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

// NOTE: (Throws error if not fitted)
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
  // TODO: Checks datatype
  vector<vector<double>> transform(const vector<vector<double>>& X) {
    // Check if the transformer is fitted, else, throw an error
    checkIsFitted();

    // input check and conversion for X/y
    //   X_inner, y_inner, metadata = self._check_X_y(X=X, y=y, return_metadata=True)
    auto Xinner; //= X; // Assuming X is already in the correct format
    auto yInner; //= vector<double>(); // Placeholder for y, if needed
    auto metadata; //= vector<string>(); // Placeholder for metadata, if needed
    checkXandY(Xinner, yInner, metadata);

    // Check if we need to vectorize

    // Placeholder for transformation logic
    // This should return a transformed version of X
    return vector<vector<double>>(); // Return an empty vector for now
  }

  // TODO: Checks datatype
  // Really easy to translate python to C++
  // Doesn't compile yet, but the logic is there
  void checkXandY(const vector<vector<double>>& X, const vector<double>& y, bool returnMetadata) {
    // Below is original python code for reference
//        if X is None:
//            if return_metadata:
//                return X, y, {}
//            else:
//                return X, y
//
//        # skip conversion if it is turned off
//        if self.get_config()["input_conversion"] != "on":
//            if return_metadata:
//                return X, y, None
//            else:
//                return X, y    // Placeholder for input validation logic
    // This should check if X and y are in the correct format and raise errors if not
    if(X.empty()){
      if(returnMetadata) {
        return X, y, {};
      } else {
        return X, y;
      }
    }

    // Skip conversion if it is turned off
    if (getConfig()["input_conversion"] != "on") {
      if (returnMetadata) {
        return X, y, {};
      } else {
        return X, y;
      }
    }
  }

};

