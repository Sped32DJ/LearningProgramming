#ifndef SHAPELET_H
#define SHAPELET_H

#include <vector>
struct Shapelet {
  // info_gain: float
  //    Calculated info gain of this shapelet.
  // series_id: int
  //    index of series within the data (X) that was passed to fit.
  // start_pos: int
  //    Start pos from the original series that this shapelet was extracted from.
  // length: int
  //    length of shapelet.
  // data: array-like
  //    The (z-normalised) shapelet data.
  float info_gain; // shapelet[0] = s[0]; range (-1.0, 1.0)
  int length; // shapelet[1] = s[1]; uint
  int startPos; // shapelet[2] = s[2]; start pos from original series; uint
  int shapeletDimension; // shapelet[3] = s[3]; uint
  int index; // shapelet[4] = s[4]; index of instance the shapelet was extracted from in fit; uint
  char classValue; // shapelet[5] = self.classes_[s[5]]; NOTE: np.str_{'1 || 2'}; class value of shapelet, only holds 1 or 2
  std::vector<double> zNormalisedValues; // shapelet[6] = z-normalise_series(X[s[4], s[3], s[2]: s[2] + s[1]]); z-normalized shapelet array


  // Real: float (range: 0.0-1.0) info_gain, int (length), int, int, int, np.str_{'1 || 2'}, vector<double> data(length)
  // (7 elements inside a shapelet)
//    shapelets : list
//        The stored shapelets and relating information after a dataset has been
//        processed.
//        Each item in the list is a tuple containing the following 7 items:
//        (shapelet information gain, shapelet length, start position the shapelet was
//        extracted from, shapelet dimension, index of the instance the shapelet was
//        extracted from in fit, class value of the shapelet, The z-normalised shapelet
//        array)  //
  Shapelet(float ig, int len, int start, int dim, int idx, int cls, std::vector<double> values)
    : info_gain(ig), length(len), startPos(start), shapeletDimension(dim), index(idx), classValue(cls), zNormalisedValues(values) {}
  Shapelet() : info_gain(0.0), length(0), startPos(0), shapeletDimension(0), index(0), classValue('0'), zNormalisedValues(std::vector<double>()) {}
    // Constructor
  Shapelet(float ig, int len, int start, int dim, int idx, char cls, const std::vector<double>& values)
      : info_gain(ig), length(len), startPos(start), shapeletDimension(dim), index(idx), classValue(cls), zNormalisedValues(values) {}
};

#endif // OUTPUT_H
