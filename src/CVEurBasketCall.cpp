#include <IRFXLib/CVEurBasketCall.h>
#include <IRFXLib/EurCall.h>
#include <cmath>

double CVEurBasketCall ::PayoffEigen(MatrixXd &&S) { return 0.0; }

double CVEurBasketCall ::Payoff(SamplePath &S) {
  double payoff = 0.0;
  int d = S[0].size();
  double denom = 0.0;
  for (int i = 0; i < d; i++) {
    // denom += S[0][i];
    denom += S.front()[i];
  }

  for (int i = 0; i < d; i++) {
    double kj = K * S.front()[i] / denom;
    payoff += max(S.back()[i] - kj, 0.0);
  }
  return payoff;
}

double CVEurBasketCall::PriceByBSFormula(BSModel Model) {

  double a = exp(-Model.r * T) * Model.S0[0] *
             exp((m + 1.0) * T / (2.0 * m) *
                 (Model.r + (((2.0 * m + 1.0) / (3.0 * m) - 1.0) *
                             Model.sigma[0] * Model.sigma[0]) /
                                2.0));
  double b = Model.sigma[0] * sqrt((m + 1.0) * (2.0 * m + 1.0) / (6.0 * m * m));
  EurCall G(T, K);
  Price = G.PriceByBSFormula(a, b, Model.r);
  return Price;
}