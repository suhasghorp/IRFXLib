#include <IRFXLib/BSModelEigen.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <unsupported/Eigen/MatrixFunctions>

const double pi = 4.0 * atan(1.0);

VectorXd BSModelEigen::Gauss(int d) {
  VectorXd Z(d);
  for (int j = 0; j < d; j++)
    Z[j] = BSModelEigen::nd(BSModelEigen::mtEngine);
  return Z;
}

MatrixXd BSModelEigen::GenerateSamplePath(double T, int m) const {
  VectorXd St = S0;
  const int d = S0.size();
  MatrixXd S(S0.size(), m);
  S.setZero();
  S.col(0) = S0;

  for (int k = 1; k < m; k++) {
    VectorXd left = (T / m) * (((-0.5) * (sigma.array().square())).array() + r);
    VectorXd right = sqrt(T / m) * (C * Gauss(d)).array();
    VectorXd sum = left.array() + right.array();
    S.col(k) = St.array() * (sum.array().exp());
    // S.row(k) = St * exp(((T / m) * (((-0.5) * sigma * sigma).array() +
    // r).array()) + (sqrt(T / m) * (C * Gauss(d))));
    St = S.col(k);
  }
  return S;
}
