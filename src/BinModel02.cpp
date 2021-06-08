//
// Created by suhasghorp on 5/13/2021.
//

#include "IRFXLib/BinModel02.h"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

namespace lecture2 {

BinModel GetInputData() {
  double S0{}, sigma{}, R{}, T{}, Q{};
  int N{};
  cout << "Enter Spot: ";
  cin >> S0;
  cout << "Enter Time to Maturity in years: ";
  cin >> T;
  cout << "Enter Volatility (e.g. 0.2): ";
  cin >> sigma;
  cout << "Enter Interest Rate (e.g. 0.05): ";
  cin >> R;
  cout << "Enter cost of carry (e.g. 0.01): ";
  cin >> Q;
  cout << "Enter Steps to Expiry N: ";
  cin >> N;
  cout << endl;

  BinModel binModel(S0, R, Q, T, sigma, N);

  return binModel;
}

BinModel::BinModel(double s_0, double r, double q, double t, double sigma,
                   int n)
    : S0(s_0), R(r), Q(q), T(t), sigma(sigma), N(n) {

  dt = T / N;
  U = exp(sigma * sqrt(dt));
  D = 1.0 / U;

  assert((S0 > 0.0 && U > -1.0 && D > -1.0 && D <= U && R >= -1.0) &&
         "Illegal Data Ranges,Terminating");
}

const double BinModel::RiskNeutProb() const {
  return (exp((R - Q) * dt) - D) / (U - D);
}

double BinModel::S(int n, int i) const {
  // return S0 * pow(1+U, i ) * pow(1+D, n - i ) ;
  return S0 * pow(U, i) * pow(D, n - i);
}

double BinModel::GetR() const { return R; }

double BinModel::GetQ() const { return Q; }

double BinModel::GetS0() const { return S0; }

double BinModel::GetT() const { return T; }

int BinModel::GetN() const { return N; }

double BinModel::GetSigma() const { return sigma; }

double BinModel::getDt() const { return dt; }

} // namespace lecture2
