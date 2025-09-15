#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>

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
  return best_dist / length;
  //return 1 / length * best_dist; // This was in the original code (???) // Check results
}

#endif
