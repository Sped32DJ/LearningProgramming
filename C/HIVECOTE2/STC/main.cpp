#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Shapelet is a tuple
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
  vector<double> zNormalisedValues; // shapelet[6] = z-normalise_series(X[s[4], s[3], s[2]: s[2] + s[1]]); z-normalized shapelet array


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
  Shapelet(float ig, int len, int start, int dim, int idx, int cls, vector<double> values)
    : info_gain(ig), length(len), startPos(start), shapeletDimension(dim), index(idx), classValue(cls), zNormalisedValues(values) {}
  Shapelet() : info_gain(0.0), length(0), startPos(0), shapeletDimension(0), index(0), classValue('0'), zNormalisedValues(vector<double>()) {}

};

// vector<vector<int>> series, vector<double> shapelet,
// vector<vector<uint>> sorted_indices (each vector<vector> has different size), vector<uint> position, vector<int> length
double _online_shapelet_distance(const vector<double>& series, const vector<double>& shapelet,
                                 vector<double>& sorted_indices, int& position, int& length) {
  // Subseq = series[pos : pos+length]
  vector<double> subseq(length); // NOTE: Really should be vector<uint>
  // This vector holds many vectors
  for(int i = 0; i < length; ++i ){
    subseq.at(i) = series.at(i + position);
  }

  double sum = 0.0;
  double sum2 = 0.0;

  for(double val : subseq) {
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
    best_dist += pow(shapelet[j] - subseq[j] , 2);
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

      //TODO: Figure out below
      for(int j = 0; j < length; ++j){
        double val = use_std ? (series.at(pos + sorted_indices.at(j)) - mean) / std :  0.0;
        double temp = shapelet.at(sorted_indices.at(j)) - val;
        dist += temp*temp;

        if(dist > best_dist) break;
      }

      best_dist = (dist < best_dist) ? dist : best_dist;
    }
    ++i;
  }
  return best_dist / static_cast<double>(length);
  //return 1 / length * best_dist; // This was in the original code (???) // Check results
}

// NOTE: Currently crashing, try moving this into int main() rather than stack
vector<vector<double>> _transform (vector<vector<double>>& X, vector<Shapelet>& shapelets, vector<vector<double>>& sorted_indices) {
  // Holds our output
  // output should be 8 columns, 22 rows; TODO: Figure out where these #'s come from
  vector<vector<double>> output(X.size(), vector<double>(X.at(0).size(), 0.0));
  cout << "output: " << output.size() << " " << output[0].size() << endl;
  //TODO: Something with sorted indices

  // This is the parallel part
  // Goes through every time series
  for (size_t i = 0; i < X.size(); ++i) {
    const vector<double> &series = X[i];
    vector<double> dists(shapelets.size());
    for (size_t j = 0; j < shapelets.size(); ++j) {
      Shapelet shapelet = shapelets[j]; // shapelets[i]
      vector<double> sortedIndices(shapelet.length);
      // TODO: Inputs to _online_shapelet_distance
      // dists[j] = _online_shapelet_distance(series[shapelet[3]], shapelet[6],
      // self._sorted_indices[n],
      // shapelet[2], shapelet[1]);
      // def _online_shapelet_distance(vector<uint> series, vector<double> shapelet,
      // vector<uint> sorted_indices, uint position, uint length):
      dists[j] = _online_shapelet_distance(series, shapelet.zNormalisedValues,
                                           sorted_indices[j], shapelet.startPos,
                                shapelet.length);
    }
    output[i] = dists;
  }
  return output;
};

vector<vector<double>> transform (vector<vector<double>>& Xt) {
  // Holds our output
  vector<vector<double>> Xt_new;
  return Xt_new;
};

vector<vector<double>> fillX (vector<vector<double>>& X);
vector<Shapelet> fillShapelets (vector<Shapelet>& shapelets);
vector<vector<double>> fillSortedIndices(vector<vector<double>>& sorted_indices);

int main(){

  // Below code for setting parameters (from test.py) for Transform
  // RandomShapeletTransform _transform
  int batch_size = 20;
  int max_shapelets = 10; // Not relevant since _predict is the shapelet generator
  int num_shapelets_samples = 100;
  int time_limit_in_minutes = 0;

  // Input of our trained data, ndarray [22][24]
  // TODO: Where do these numbers come from?
  // 22 vectors each holding 24 elements of data. NOTE: Data never changes
  vector<vector<double>> X(22, vector<double>(24, 0.0)); // Filled during training
  cout << "X declared";
  X = fillX(X); // Fill X with data from sample
  cout << "-> X filled "<< endl << "X: " << X.size() << " " << X[0].size() << endl;
  for (int i = 0; i < X.size(); ++i) {
    cout << "{";
    for (int j = 0; j < X[i].size(); ++j) {
      cout << X[i][j] << " ";
    }
    cout << "}" << endl;
  }
  // Opening length file
  // int lengthFile =

  // NOTE: # of shapelets & shapelet content changes based on training from _fit()
  vector<Shapelet> shapelets(9); // This should be filled during training, # of shapelets changes
  shapelets = fillShapelets(shapelets);

  // NOTE: Filling sorted_indices from _fit()
  vector<vector<double>> sorted_indices(9); // This should be filled during training, # of shapelets changes
  sorted_indices = fillSortedIndices(sorted_indices);


  // Transforming our input data, [24][9]
  // Sample of an index: small decimal values
  //  [4.50453845e-02 3.34424780e-02 3.28272484e-02 4.80882944e-02
  //  3.50738746e-02 5.75993352e-02 3.25588740e-02 4.57999218e-02
  //  1.34327924e-02]]
  vector<vector<double>> Xt;
  // TODO: Test this against the real input and expected output
  cout << "\nCalling _transform" << endl;
  Xt = _transform(X, shapelets, sorted_indices);
  cout << "Below Xt" << endl;
  for (int i = 0; i < Xt.size(); ++i) {
    cout << '{';
    for (int j = 0; j < Xt[i].size(); ++j) {
      cout << Xt[i][j] << " ";
    }
    cout << '}' << endl;
  }
  // NOTE: Xt changes based on trained shapelets
  //Xt = transform(Xt);
  //transform(Xt); // Changes the format of our data



  cout << "I love STC" << endl;
  return 0;
}

vector<Shapelet> fillShapelets (vector<Shapelet>& shapelets){
  shapelets =
{{1.0, 14, 0, 0, 6, '1', { 0.56073772, -0.16551479, -0.41083754, -0.58329215, -0.78975189,
       -0.85047534, -0.84561747, -0.74360206, -0.58815002, -0.48613462,
       -0.11936496,  0.71618976,  1.87479326,  2.4310201 }}, {1.0, 13, 3, 0, 1, '1', {-0.69528954, -0.77008279, -0.91218996, -0.91218996, -0.91779945,
       -0.83365705, -0.67846106, -0.21474292,  0.24897522,  1.3091695 ,
        1.65134861,  1.37087393,  1.35404545}}, {1.0, 11, 2, 0, 18, '2', {-0.61364035, -0.66904028, -0.73610335, -0.67778763, -0.66320871,
       -0.42994585, -0.1354515 , -0.04214636,  0.33982157,  0.85591563,
        2.77158682}}, {1.0, 10, 1, 0, 4, '1', { 1.63885465,  0.61457049, -0.05552194, -0.70646889, -0.95536036,
       -1.07023335, -0.98407861, -0.30441342,  0.00191455,  1.82073688}}, {0.758276657193, 18, 1, 0, 0, '1', {-0.38321241, -0.53935769, -0.72715405, -1.05843526, -1.10274676,
       -1.1217374 , -1.10485683, -0.93605112, -0.87274897, -0.53513755,
        0.12320472,  1.41245835,  1.52851227,  1.40190799,  1.10649799,
        0.65283264,  1.13814907,  1.017875  }}, {0.758276657193, 18, 0, 0, 11, '2', {-0.68157062, -0.85358665, -0.88005065, -0.961648  , -0.95723733,
       -0.961648  , -0.93077333, -0.7653733 , -0.61320528, -0.54042927,
       -0.01776519,  0.33288287,  1.57669105,  1.71562708,  1.01874164,
        0.93052829,  0.87539495,  1.71342174}}, {0.609986547011, 8, 4, 0, 12, '2', {-0.90930622, -0.86494982, -0.87049437, -0.55445501,  0.0554455 ,
        0.26613841,  0.68197966,  2.19564184}}, {0.531004406411, 16, 1, 0, 14, '2', {-0.76302713, -0.86397436, -0.9092976 , -0.87221495, -0.95050055,
       -0.90311716, -0.81865111, -0.59615518, -0.51992973, -0.07699801,
        0.54516653,  1.75447312,  1.8492399 ,  1.03960193,  0.96337648,
        1.12200783}},
      {0.49342260575999997, 19, 0, 0, 19, '2', {-0.90197863, -0.87549829, -0.97660504, -1.03197302, -1.00549268,
       -1.05845336, -1.02715841, -0.76716963, -0.55773422, -0.47107129,
       -0.23756285,  0.39555798,  1.48606648,  1.73161145,  1.10089792,
        0.96608892,  0.89868442,  1.13460017,  1.19719006}}};
  return shapelets;
}

vector<vector<double>> fillSortedIndices(vector<vector<double>>& sorted_indices) {
  sorted_indices =
{{13, 12,  5,  6,  4,  7, 11,  8,  3,  0,  9,  2,  1, 10}, {10, 11, 12,  9,  4,  2,  3,  5,  1,  0,  6,  8,  7}, {10,  9,  2,  3,  1,  4,  0,  5,  8,  6,  7}, {9, 0, 5, 6, 4, 3, 1, 7, 2, 8}, {12, 11, 13, 16,  5, 14,  6,  4,  3, 17,  7,  8,  2, 15,  1,  9,  0,
       10}, {13, 17, 12, 14,  3,  5,  4,  6, 15,  2, 16,  1,  7,  0,  8,  9, 11,
       10}, {7, 0, 2, 1, 6, 3, 5, 4}, {12, 11, 15, 13, 14,  4,  2,  5,  3,  1,  6,  0,  7, 10,  8,  9},
      {13, 12, 18, 17, 14,  5,  3,  6,  4,  2, 15,  0, 16,  1,  7,  8,  9,
       11, 10}};
  return sorted_indices;
};

vector<vector<double>> fillX (vector<vector<double>>& X) {
  // Data from input.txt
  X =
{{ 501,  328,  195,  218,   67,   17,   28,   72,  132,  215,  406,
    765, 1207, 1427, 1234, 1238, 1107, 1190, 1255, 1144,  905,  690,
    386,  192,},

 { 880,  752,  913,  863,  402,  112,   60,  112,  119,  186,  365,
    596,  990, 1193, 1040, 1063, 1009, 1025, 1089,  979,  706,  585,
    356,  187,},

 { 493,  389,  174,  121,   82,   36,   27,   64,  127,  203,  415,
    747, 1164, 1414, 1520, 1295, 1265, 1430, 1637, 1697, 1456, 1319,
   1179,  848,},

 { 616,  323,  162,  166,   68,   26,   34,   68,  123,  263,  815,
   1611, 1823, 2019, 1763, 1728, 1568, 1439, 1431, 1282, 1078,  857,
    498,  248,},

 { 389,  276,  161,  124,   35,   26,   51,   75,   71,  126,  225,
    496,  968, 1128, 1117,  993,  819,  879,  998, 1057, 1014,  987,
    836,  680,},

 { 548,  384,  245,  147,  101,   40,   30,   66,   77,  209,  380,
    650, 1229, 1527, 1456, 1333, 1326, 1293, 1582, 1713, 1490, 1270,
   1206,  752,},

 { 369,  297,  171,  108,   90,   47,   37,   73,  164,  203,  325,
    584, 1160, 1371, 1238, 1213, 1268, 1370, 1530, 1524, 1343, 1020,
    884,  585,},

 { 418,  350,  116,   93,   90,   37,   27,   52,  100,  155,  392,
    697, 1093, 1413, 1353, 1247, 1280, 1357, 1520, 1555, 1212, 1022,
    817,  502,},

 { 504,  273,  175,  135,   62,   44,   35,   65,  112,  180,  370,
    668, 1205, 1491, 1390, 1329, 1342, 1455, 1653, 1739, 1537, 1222,
   1041,  665,},

 { 498,  339,  170,  194,   94,   48,   31,   60,  164,  166,  355,
    777, 1251, 1358, 1265, 1280, 1226, 1379, 1493, 1561, 1198,  907,
    919,  731,},

 { 478,  405,  237,  154,   62,   61,   29,   50,   78,  242,  362,
    836, 1462, 1431, 1459, 1315, 1214, 1221, 1299, 1239, 1208,  966,
    653,  296,},

 { 595,  300,  190,  137,   44,   34,   22,   56,  100,  186,  405,
    702, 1267, 1459, 1360, 1179, 1276, 1350, 1597, 1609, 1373, 1051,
    897,  592,},

 { 129,   91,   47,   15,   46,   21,   38,   90,  203,  226,  316,
    453,  850, 1133,  852,  793,  854,  977, 1135, 1041,  896,  822,
    555,  366,},

 { 181,  116,  103,   53,   35,   46,   52,   98,  252,  202,  353,
    642, 1181, 1324,  937,  987,  932, 1242, 1344, 1327, 1083,  834,
    912,  413,},

 { 349,  187,  100,   65,   65,   40,   20,   41,   48,  104,  461,
    771, 1449, 1622, 1389, 1446, 1240, 1268, 1320, 1449, 1438, 1318,
   1075,  484,},

 { 219,  143,  120,   27,   15,   23,   36,   88,  223,  212,  317,
    487, 1002, 1063,  718,  773,  759,  989, 1156, 1211, 1107, 1094,
    879,  582,},

 { 124,   51,   37,   12,   15,   23,   31,   89,  188,  316,  442,
    656, 1250, 1427, 1229,  993,  944, 1056, 1144, 1068,  855,  681,
    411,  245,},

 { 540,  484,  252,  160,  158,   46,   49,   53,  141,  167,  459,
    806, 1393, 1638, 1545, 1441, 1389, 1495, 1597, 1822, 1653, 1261,
    876,  679,},

 { 103,   78,   34,   19,   29,   24,   26,   67,  168,  185,  315,
    670, 1011, 1089,  957,  766,  790,  946, 1119, 1163, 1030,  718,
    529,  225,},

 { 105,   66,   55,   21,   36,   16,   26,   87,  266,  201,  352,
    607, 1095, 1245,  870,  769,  787,  993, 1138,  936,  712,  532,
    312,  160,},

 {  95,   63,   45,   26,    3,   23,   28,  108,  209,  241,  372,
    549, 1206, 1223, 1156, 1102, 1083, 1107, 1109, 1193,  900,  660,
    442,  226,},

 { 193,  195,   90,   46,   49,   15,   21,   45,  106,  147,  365,
    767, 1120, 1125, 1235, 1056, 1031, 1006, 1131, 1034,  856,  587,
    317,  224,}};
    return X;
};
