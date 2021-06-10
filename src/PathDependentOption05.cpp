#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <IRFXLib/PathDependentOption05.h>
#include <cmath>
#include <execution>
#include <iostream>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

double PathDepOption::PriceByMCEigen(BSModelEigen &&Model, long N) {
  double H = 0.0, Hsq = 0.0;
  // pre-compute all the sample paths in parallel
  auto t1 = high_resolution_clock::now();
  std::vector<int> v(N);
  std::vector<MatrixXd> SVec(N);
  std::iota(std::begin(v), std::end(v), 0);
  std::transform(std::execution::par, v.begin(), v.end(), SVec.begin(),
                 [&](int x) { return Model.GenerateSamplePath(T, m); });

  for (long i = 0; i < v.size(); i++) {
    double payoff = PayoffEigen(std::move(SVec[i]));
    H = (i * H + payoff) / (i + 1.0);
    Hsq = (i * Hsq + pow(payoff, 2.0)) / (i + 1.0);
  }
  auto t2 = high_resolution_clock::now();
  auto ms_int = duration_cast<milliseconds>(t2 - t1);
  std::cout << "(PriceByMCEigen took: " << ms_int.count() << "ms) ";
  Price = exp(-Model.r * T) * H;
  PricingError = exp(-Model.r * T) * sqrt(Hsq - H * H) / sqrt(N - 1.0);

  return Price;
}

double PathDepOption::PriceByMC(BSModel &Model, long N) {
  double H = 0.0, Hsq = 0.0;
  SamplePath S(m);
  auto t1 = high_resolution_clock::now();
  for (long i = 0; i < N; i++) {
    Model.GenerateSamplePath(T, m, S);
    H = (i * H + Payoff(S)) / (i + 1.0);
    Hsq = (i * Hsq + pow(Payoff(S), 2.0)) / (i + 1.0);
  }
  auto t2 = high_resolution_clock::now();
  auto ms_int = duration_cast<milliseconds>(t2 - t1);
  std::cout << "(PriceByMC took: " << ms_int.count() << "ms) ";
  Price = exp(-Model.r * T) * H;
  PricingError = exp(-Model.r * T) * sqrt(Hsq - H * H) / sqrt(N - 1.0);

  return Price;
}
double ArithmAsianCall::PayoffEigen(MatrixXd &&S) {
  double Ave = 0.0;
  int d = S.col(0).size();
  VectorXd one(d);
  one.setOnes();
  for (int k = 0; k < m; k++) {
    Ave = (k * Ave + (one.dot(S.col(k)))) / (k + 1.0);
  }
  if (Ave < K)
    return 0.0;
  return Ave - K;
}
double ArithmAsianCall::Payoff(SamplePath &S) {
  double Ave = 0.0;
  int d = S[0].size();
  Vector one(d);
  for (int i = 0; i < d; i++)
    one[i] = 1.0;
  for (int k = 0; k < m; k++) {
    Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
  }
  if (Ave < K)
    return 0.0;
  return Ave - K;
}

double PathDepOption::PriceByVarRedMC(BSModel &Model, long N,
                                      PathDepOption &CVOption) {
  DifferenceOfOptions VarRedOpt(T, m, this, &CVOption);
  Price =
      VarRedOpt.PriceByMC(Model, N); //+ CVOption.PriceByBSFormula ( Model ) ;
  PricingError = VarRedOpt.PricingError;
  return Price;
}

double EurBasketCall::Payoff(SamplePath &S) {

  double sum = 0.0;
  int d = S[0].size();
  for (int i = 0; i < d; i++) {
    // sum += S[m-1][i];
    sum += S.back()[i];
  }
  return sum - K > 0.0 ? sum - K : 0.0;
}

double EurBasketCall::PayoffEigen(MatrixXd &&S) {

  double sum = 0.0;
  int d = S.col(0).size();
  for (int i = 0; i < d; i++) {
    sum += S.coeffRef(d, m - 1);
    // sum += S[m-1][i];
    // sum += S.back()[i];
  }
  return sum - K > 0.0 ? sum - K : 0.0;
}
