#include <IRFXLib/BinModel02.h>
#include <IRFXLib/Option06.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace lecture2;

double EurOption::PriceByCRR(BinModel Model) {

  double q = Model.RiskNeutProb(N);
  double Price[N + 1];
  for (int i = 0; i <= N; i++) {
    Price[i] = Payoff(Model.S(N, i));
  }
  for (int n = N - 1; n >= 0; n--) {
    for (int i = 0; i <= n; i++) {
      Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) *
                 exp(-Model.GetR() * Model.getDt());
    }
  }
  return Price[0];
}

double Call::Payoff(double z) {
  if (z > K)
    return z - K;
  return 0.0;
}

int Call::GetInputData() {
  cout << " Enter Call Option data : " << endl;
  int N;
  cout << " Enter Steps to Expiry N: ";
  cin >> N;
  SetN(N);
  cout << " Enter Strike Price K: ";
  cin >> K;
  cout << endl;
  return 0;
}

double Put::Payoff(double z) {
  if (z < K)
    return K - z;
  return 0.0;
}

int Put::GetInputData() {
  cout << " Enter Put Option data : " << endl;
  int N;
  cout << " Enter Steps to Expiry N: ";
  cin >> N;
  SetN(N);
  cout << " Enter Strike Price K: ";
  cin >> K;
  cout << endl;
  return 0;
}

double DoubleDigital::Payoff(double z) {
  if (K1 <= z && z <= K2)
    return 1.0;
  return 0.0;
}

double DoubleDigital::GetK1() const { return K1; }
double DoubleDigital::GetK2() const { return K2; }

int DoubleDigital::GetInputData() {
  cout << " Enter Double Digital Option data : " << endl;
  int N;
  cout << " Enter Steps to Expiry N: ";
  cin >> N;
  SetN(N);
  cout << " Enter First Strike Price K1: ";
  cin >> K1;
  cout << " Enter Second Strike Price K2: ";
  cin >> K2;
  cout << endl;
  return 0;
}
