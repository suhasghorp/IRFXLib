//
// Created by suhasghorp on 5/22/2021.
//
#include <IRFXLib/BinLattice02.h>
#include <IRFXLib/BinModel02.h>
#include <IRFXLib/Options09.h>
#include <cmath>
#include <iostream>
using namespace std;

namespace lecture3 {

double EurOption::PriceByCRR(const lecture2::BinModel &Model) {
  double q = Model.RiskNeutProb();
  int N = GetN();
  vector<double> Price(N + 1);
  for (int i = 0; i <= N; i++) {
    Price[i] = PayOff(Model.S(N, i));
  }
  for (int n = N - 1; n >= 0; n--) {
    for (int i = 0; i <= n; i++) {
      Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) *
                 exp(-Model.GetR() * Model.getDt());
    }
  }
  return Price[0];
}

double AmOption::PriceBySnell(const lecture2::BinModel &Model,
                              BinLattice<double> &PriceTree,
                              BinLattice<bool> &StoppingTree) {
  double q = Model.RiskNeutProb();
  int N = GetN();
  PriceTree.SetN(N);
  StoppingTree.SetN(N);
  double ContVal;

  for (int i = 0; i <= N; i++) {
    PriceTree.SetNode(N, i, PayOff(Model.S(N, i)));
    StoppingTree.SetNode(N, i, 1);
  }

  for (int n = N - 1; n >= 0; n--) {
    for (int i = 0; i <= n; i++) {
      ContVal = (q * PriceTree.GetNode(n + 1, i + 1) +
                 (1 - q) * PriceTree.GetNode(n + 1, i)) *
                exp(-Model.GetR() * Model.getDt());
      PriceTree.SetNode(n, i, PayOff(Model.S(n, i)));
      StoppingTree.SetNode(n, i, 1);
      // 0 - option should NOT be exercised at given node
      if (ContVal > PriceTree.GetNode(n, i)) {
        PriceTree.SetNode(n, i, ContVal);
        StoppingTree.SetNode(n, i, 0);
      } else if (PriceTree.GetNode(n, i) == 0.0) {
        StoppingTree.SetNode(n, i, 0);
      }
    }
  }
  return PriceTree.GetNode(0, 0);
}

int Call::GetInputData() {
  cout << "Enter Call Option data : " << endl;
  cout << "Enter Strike Price K: ";
  cin >> K;
  cout << endl;
  return 0;
}
int Put::GetInputData() {
  cout << "Enter Put Option data : " << endl;
  cout << "Enter Strike Price K: ";
  cin >> K;
  cout << endl;
  return 0;
}

double Call::PayOff(double z) {
  if (z > K)
    return z - K;
  return 0.0;
}
double Put::PayOff(double z) {
  if (z < K)
    return K - z;
  return 0.0;
}
} // namespace lecture3
