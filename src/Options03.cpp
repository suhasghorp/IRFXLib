#include <IRFXLib/BinModel01.h>
#include <IRFXLib/Options03.h>
#include <math.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <spdlog/spdlog.h>

using namespace std;

namespace lecture1 {

void interchange(double &a, double &b) {
  double c = a;
  a = b, b = c;
}

void bubblesort(double a[], int N) {

  for (int i = 1; i < N; i++) {
    for (int j = 1; j <= N - i; j++) {
      if (a[j - 1] > a[j])
        interchange(a[j - 1], a[j]);
    }
  }
}

int GetInputData(int &N, double &K) {
  cout << " Enter Steps to Expiry N: ";
  cin >> N;
  cout << " Enter Strike price K: ";
  cin >> K;
  cout << endl;
  return 0;
}

// pricing European option
Result PriceByCRR(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K, double (*Payoff)(double z, double K)) {
  double dt = T / N;
  double U = exp(sigma * sqrt(dt));
  //D = 1/U
  double D = 1.0 / U;
  double q = RiskNeutProb(U, D, exp(R * dt));
  // double Price[N+1];
  vector<double> Value(N + 1);
  vector<vector<double>> Price(N + 1, vector<double>(N + 1));
  double gamma = 0.0;double delta = 0.0;

  for (int i = 0; i <= N; i++) {
    Price[N][i] = S(S0, U, D, N, i);
    Value[i] = Payoff(Price[N][i], K);
  }

  for (int n = N - 1; n >= 0; n--) {
    for (int i = 0; i <= n; i++) {
      Price[n][i] = S(S0, U, D, n, i);
      Value[i] = (q * Value[i + 1] + (1 - q) * Value[i]) * exp(-R * dt);
      if (execType == ExerciseType::American) {
        double earlyExerciseValue = Payoff(Price[n][i], K);
        Value[i] = max(Value[i], earlyExerciseValue);
      }
    }
    if (n == 2){
      double delta1 = ((Value[2] - Value[1])) / (Price[2][2] - Price[2][1]);
      double delta2 = ((Value[1] - Value[0])) / (Price[2][1] - Price[2][0]);
      gamma = (delta1 - delta2)/ (0.5 * (Price[2][2] - Price[2][0]));

    }

    if (n == 1){
      delta = ((Value[1] - Value[0])) / (Price[1][1] - Price[1][0]);
    }
  }

  struct Result result;
  result.price = Value[0]; result.delta = delta; result.gamma = gamma;
  return result;

}

double FastBinomialCoeff(int i, int N) {
  double res = 1;
  if (i > N - i)
    i = N - i;

  // calc value of
  for (int j = 0; j < i; ++j) {
    res *= (N - j);
    res /= (j + 1);
  }
  return res;
}

double fact(int n) { return (n == 0) || (n == 1) ? 1 : n * fact(n - 1); }

double BinomialCoeff(int i, int N) { return fact(N) / (fact(i) * fact(N - i)); }

double NodeValue(int i, int N, double q) {
  return FastBinomialCoeff(i, N) * pow(q, i) * pow(1.0 - q, (N - i));
  // return BinomialCoeff(i, N) * pow(q, i) * pow(1.0 - q, (N - i));
}

double PriceByAnalytical(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K, double (*Payoff)(double z, double K)) {
  double dt = T / N;
  double U = exp(sigma * sqrt(dt));
  //D = 1/U
  double D = 1.0 / U;
  double q = RiskNeutProb(U, D, exp(R * dt));
  double total = 0.0;
  double Price = 0.0;
  vector<double> NV;
  for (int i = 0; i <= N; ++i) {
    Price = Payoff(S(S0, U, D, N, i), K);
    double nv = NodeValue(i, N, q);
    NV.push_back(nv);
    total += nv * Price;
  }
  std::ofstream fout;
  fout.open("density_plot.txt");
  fout.precision(10);
  copy(NV.begin(), NV.end(), std::ostream_iterator<double>(fout, "\n"));
  fout.close();
  return total / exp(R * T);
}

double PriceByBS(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K, double (*Payoff)(double z, double K)) {
  double dt = T / N;
  double U = exp(((R - (pow(sigma, 2) / 2)) * dt) + (sigma * sqrt(dt))) - 1.0;
  //D = 1/U
  double D = exp(((R - (pow(sigma, 2) / 2)) * dt) - (sigma * sqrt(dt))) - 1.0;
  double q = RiskNeutProbBS(U, D, exp(R * dt));
  vector<double> Value(N + 1);
  vector<vector<double>> Price(N + 1, vector<double>(N + 1));

  for (int n = 0; n <= N; n++) {
    for (int i = 0; i <= N; i++) {
      Price[n][i] = S_BS(S0, U, D, n, i);
      if (n == N)
        Value[i] = Payoff(Price[n][i], K);
    }
  }

  for (int n = N - 1; n >= 0; n--) {
    for (int i = 0; i <= n; i++) {
      Value[i] = (q * Value[i + 1] + (1 - q) * Value[i]) * exp(-R * dt);
      if (execType == ExerciseType::American) {
        double earlyExerciseValue = Payoff(Price[n][i], K);
        Value[i] = max(Value[i], earlyExerciseValue);
      }
    }
  }

  return Value[0];

}

double CallPayoff(double z, double K) {
  if (z > K)
    return z - K;
  return 0.0;
}

double PutPayoff(double z, double K) {
  if (K > z)
    return K - z;
  return 0.0;
}

double DigitalCallPayoff(double z, double K) {
  if (z > K)
    return 1.0;
  return 0.0;
}

double DigitalPutPayoff(double z, double K) {
  if (K > z)
    return 1.0;
  return 0.0;
}

} // namespace lecture1