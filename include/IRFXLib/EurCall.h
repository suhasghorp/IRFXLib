//
// Created by suhasghorp on 6/1/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_EURCALL_H_
#define IRFXLIB_INCLUDE_IRFXLIB_EURCALL_H_
class EurCall {
public:
  double T, K;
  EurCall(double T_, double K_) {
    T = T_;
    K = K_;
  }
  double dplus(double S0, double sigma, double r);
  double dminus(double S0, double sigma, double r);
  double PriceByBSFormula(double S0, double sigma, double r);
  double VegaByBSFormula(double S0, double sigma, double r);
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_EURCALL_H_
