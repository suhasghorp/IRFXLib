//
// Created by suhasghorp on 6/1/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_GMTRASIANCALL_H_
#define IRFXLIB_INCLUDE_IRFXLIB_GMTRASIANCALL_H_
#include <IRFXLib/PathDependentOption01.h>

class GmtrAsianCall : public PathDepOption {
public:
  double K;
  GmtrAsianCall(double T_, double K_, int m_) {
    T = T_;
    K = K_;
    m = m_;
  }
  double Payoff(SamplePath &S);
  double PriceByBSFormula(BSModel Model);
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_GMTRASIANCALL_H_
