//
// Created by suhasghorp on 6/7/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_BSMODELEigen_H_
#define IRFXLIB_INCLUDE_IRFXLIB_BSMODELEigen_H_

#include <Eigen/Dense>
#include <chrono>
#include <cmath>
#include <ctime>
#include <random>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class BSModelEigen {
public:
  VectorXd S0, sigma;
  double r;
  MatrixXd C;

  BSModelEigen(VectorXd &&S0_, double r_, MatrixXd &&C_)
      : S0(S0_), r(r_), C(C_) {
    int d = S0.size();
    sigma.resize(d);
    for (int j = 0; j < d; j++) {
      double sum = C.row(j).dot(C.row(j));
      sigma[j] = sqrt(sum);
    }
  }
  [[nodiscard]] MatrixXd GenerateSamplePath(double T, int m) const;
  static VectorXd Gauss(int d);

  static double GetZ() {
    static std::random_device randomness_device{};
    static std::mt19937_64 mtEngine{randomness_device()};
    static std::normal_distribution<> nd;
    return nd(mtEngine);
  }
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_BSMODELEigen_H_
