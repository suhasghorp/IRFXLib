//
// Created by suhasghorp on 6/2/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_BSMODEL02_H_
#define IRFXLIB_INCLUDE_IRFXLIB_BSMODEL02_H_

#include <Eigen/Dense>
#include <IRFXLib/matrix.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

using Eigen::MatrixXd;

typedef vector<Vector> SamplePath;

class BSModel {
public:
  Vector S0, sigma;
  double r;
  Matrix C;
  std::random_device randomness_device{};
  std::mt19937_64 mtEngine{randomness_device()};

  BSModel(Vector S0_, double r_, Matrix C_) : S0(S0_), r(r_), C(C_) {
    srand(time(NULL));
    int d = S0.size();
    sigma.resize(d);
    for (int j = 0; j < d; j++)
      sigma[j] = sqrt(C[j] ^ C[j]);
  }
  void GenerateSamplePath(double T, int m, SamplePath &S);
  Vector Gauss(int d);
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_BSMODEL02_H_
