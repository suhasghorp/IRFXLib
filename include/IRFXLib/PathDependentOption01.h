//
// Created by suhasghorp on 5/29/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_PATHDEPENDENTOPTION01_H_
#define IRFXLIB_INCLUDE_IRFXLIB_PATHDEPENDENTOPTION01_H_

#include <IRFXLib/BSModel01.h>
class PathDepOption {
public:
  double T, Price, PricingError, delta;
  int m;
  double PriceByMC(BSModel Model, long N, double epsilon);
  double PriceByMC(BSModel Model, long N);
  double PriceByVarRedMC(BSModel Model, long N, PathDepOption &CVOption);
  virtual double PriceByBSFormula(BSModel Model) { return 0.0; };
  virtual double Payoff(SamplePath &S) = 0;
};

class DifferenceOfOptions : public PathDepOption {

public:
  PathDepOption *Ptr1;
  PathDepOption *Ptr2;
  DifferenceOfOptions(double T_, int m_, PathDepOption *Ptr1_,
                      PathDepOption *Ptr2_) {
    T = T_;
    m = m_;
    Ptr1 = Ptr1_;
    Ptr2 = Ptr2_;
  }
  double Payoff(SamplePath &S) { return Ptr1->Payoff(S) - Ptr2->Payoff(S); }
};

class ArithmAsianCall : public PathDepOption {
public:
  double K;
  ArithmAsianCall(double T_, double K_, int m_) : K(K_) {
    T = T_;
    m = m_;
  }
  double Payoff(SamplePath &S) override;
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_PATHDEPENDENTOPTION01_H_
