#include <IRFXLib/BSModel02.h>
#include <cmath>
#include <cstdlib>
#include <random>

using std::mt19937_64;
using std::normal_distribution;

const double pi = 4.0 * atan(1.0);

double Gauss() {
  double U1 = (rand() + 1.0) / (RAND_MAX + 1.0);
  double U2 = (rand() + 1.0) / (RAND_MAX + 1.0);
  return sqrt(-2.0 * log(U1)) * cos(2.0 * pi * U2);
}

Vector BSModel::Gauss(int d) {
  Vector Z(d);
  // for (int j = 0; j < d; j++) Z[j] = Gauss();
  normal_distribution<> nd;
  for (int j = 0; j < d; j++)
    Z[j] = nd(mtEngine);
  return Z;
}

void BSModel::GenerateSamplePath(double T, int m, SamplePath &S) {
  Vector St = S0;
  S[0] = S0;
  int d = S0.size();

  for (int k = 1; k < m; k++) {
    S[k] = St * exp(((T / m) * (r + (-0.5) * sigma * sigma)) +
                    (sqrt(T / m) * (C * Gauss(d))));
    St = S[k];
  }
}
