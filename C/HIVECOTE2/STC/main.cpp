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

vector<vector<double>> fillX (vector<vector<double>>& X);

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
  X = fillX(X);
  cout << "X: " << X.size() << " " << X[0].size() << endl;


  // Transforming our input data, [24][9]
  // Sample of an index: small decimal values
  //  [4.50453845e-02 3.34424780e-02 3.28272484e-02 4.80882944e-02
  //  3.50738746e-02 5.75993352e-02 3.25588740e-02 4.57999218e-02
  //  1.34327924e-02]]
  vector<vector<double>> Xt;
  // TODO: Test this against the real input and expected output
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

