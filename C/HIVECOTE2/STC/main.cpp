#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Shapelet {
  // series_id: int
  //    index of series within the data (X) that was passed to fit.
  // start_pos: int
  //    Start pos from the original series that this shapelet was extracted from.
  // length: int
  //    length of shapelet.
  // info_gain: float
  //    Calculated info gain of this shapelet.
  // data: array-like
  //    The (z-normalised) shapelet data.
  int seriesID; // shapelet[0] = s[0]
  int startPos; // shapelet[1] = s[1]
  int length; // shapelet[2] = s[2]
  vector<double> values; // shapelet[3] = s[3], TODO: figure out the size of vector, at least the max
  int classLabel; // shapelet[4] = s[4]
  vector<double> classes;  // shapelet[5] = self.classes_[s[5]] (numpy.ndarray)  NOTE: May actually be int
  vector<double> normalizedValues;  // shapelet[6] = z_normalise_series(X[s[4], s[3], s[2] : s[2] + s[1]])
  Shapelet(int seriesID, int startPos, int length, vector<double> values, int classLabel, vector<double> classes)
    : seriesID(seriesID), startPos(startPos), length(length), values(values), classLabel(classLabel), classes(classes) {}
};

double _online_shapelet_distance(const vector<double>& series, const Shapelet& shapelet,
                                 vector<double>& sorted_indices, int& position, int& length);

vector<vector<double>> _transform (vector<vector<double>>& X) {
  // Holds our output
  // output should be 8 columns, 22 rows; TODO: Figure out where these #'s come from
  vector<vector<double>> output(X.size(), vector<double>(X.at(0).size(), 0.0));
  cout << "output: " << output.size() << " " << output[0].size() << endl;

  // AI generated sample shapelet
  Shapelet shapelet(0, 0, 5, vector<double>{1.0, 2.0, 3.0, 4.0, 5.0}, 0, vector<double>{0.0});
  vector<Shapelet> shapelets = {shapelet}; // Add more shapelets as needed

  // This is the parallel part
  // Goes through every time series
  for (size_t i = 0; i < X.size(); ++i) {
    const vector<double> &series = X[i];
    vector<double> dist(shapelets.size());
    vector<double> sorted_indices(shapelet.length); // or shapelets.size()?
    for (size_t j = 0; j < shapelets.size(); ++j) {
      Shapelet currShape = shapelets[j]; // shapelets[j];
      _online_shapelet_distance(shapelet.values, shapelet,
                                sorted_indices,
                                shapelet.startPos, shapelet.length);
    }
  }
  return output;
};

vector<vector<double>> transform (vector<vector<double>>& Xt) {
  // Holds our output
  vector<vector<double>> Xt_new;
  return Xt_new;
};


int main(){

  // Below code for setting parameters (from test.py) for Transform
  // RandomShapeletTransform _transform
  int batch_size = 20;
  int max_shapelets = 10;
  int num_shapelets_samples = 100;
  int time_limit_in_minutes = 0;

  // Input of our trained data, ndarray [22][24]
  // TODO: Where do these numbers come from?
  // 22 vectors each holding 24 elements of data
  vector<vector<double>> X(22, vector<double>(24, 0.0));
  cout << "X: " << X.size() << " " << X[0].size() << endl;


  // Transforming our input data, [24][9]
  // Sample of an index: small decimal values
  //  [4.50453845e-02 3.34424780e-02 3.28272484e-02 4.80882944e-02
  //  3.50738746e-02 5.75993352e-02 3.25588740e-02 4.57999218e-02
  //  1.34327924e-02]]
  vector<vector<double>> Xt;
  Xt = _transform(X);
  Xt = transform(Xt);
  transform(Xt); // Changes the format of our data




  cout << "I love STC" << endl;
  return 0;
}

double _online_shapelet_distance(const vector<double>& series, const Shapelet& shapelet,
                                 vector<double>& sorted_indices, double& position, int& length) {
  vector<double> subseq(length);
  // Subseq = series[pos : pos+length]
  for(int i = 0; i < length; ++i ){
    subseq.at(i) = series.at(i + position);
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

//  // Fix this to where it works properly with shapelets
  //  original code:
  //  for i, n in zip(shapelet, subseq):
  //    best_dist += (i - n) ** 2
  double best_dist = 0.0;
  for(int j = 0; j < length; ++j){
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
  return best_dist / length;
  //return 1 / length * best_dist; // This was in the original code (???) // Check results
}

