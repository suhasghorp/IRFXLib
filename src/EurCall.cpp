#include <IRFXLib/EurCall.h>
#include <cmath>
double N(double x) {
  double gamma = 0.2316419;
  double a1 = 0.319381530;
  double a2 = -0.356563782;
  double a3 = 1.781477937;
  double a4 = -1.821255978;
  double a5 = 1.330274429;
  double pi = 4.0 * atan(1.0);
  double k = 1.0 / (1.0 + gamma * x);
  if (x >= 0.0) {
    return 1.0 - ((((a5 * k + a4) * k + a3) * k + a2) * k + a1) * k *
                     exp(-x * x / 2.0) / sqrt(2.0 * pi);
  } else
    return 1.0 - N(-x);
}

double EurCall::dplus(double S0, double sigma, double r) {
  return (log(S0 / K) + (r + 0.5 * pow(sigma, 2.0)) * T) / (sigma * sqrt(T));
}
double EurCall::dminus(double S0, double sigma, double r) {
  return dplus(S0, sigma, r) - sigma * sqrt(T);
}

double EurCall::PriceByBSFormula(double S0, double sigma, double r) {
  double dp = dplus(S0, sigma, r);
  double dm = dminus(S0, sigma, r);
  return S0 * N(dp) - K * exp(-r * T) * N(dm);
}

double EurCall::VegaByBSFormula(double S0, double sigma, double r) {
  double pi = 4.0 * atan(1.0);
  return S0 * exp(-dplus(S0, sigma, r) * dplus(S0, sigma, r) / 2) * sqrt(T) /
         sqrt(2.0 * pi);
}