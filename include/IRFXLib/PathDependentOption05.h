//
// Created by suhasghorp on 6/2/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_PATHDEPENDENTOPTION05_H_
#define IRFXLIB_INCLUDE_IRFXLIB_PATHDEPENDENTOPTION05_H_

#include <IRFXLib/BSModel02.h>
#include <IRFXLib/BSModelEigen.h>
class PathDepOption {
public:
  double T{0.0}, Price{0.0}, PricingError{0.0}, delta{0.0};
  int m{0};
  double PriceByMC(BSModel &Model, long N);
  virtual double PriceByMCEigen(BSModelEigen &&Model, long N);
  double PriceByVarRedMC(BSModel &Model, long N, PathDepOption &CVOption);
  virtual double PriceByBSFormula(BSModel Model) { return 0.0; };
  virtual double Payoff(SamplePath &S) = 0;
  virtual double PayoffEigen(MatrixXd &&S) = 0;
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
  double Payoff(SamplePath &S) override {
    return Ptr1->Payoff(S) - Ptr2->Payoff(S);
  }
  double PayoffEigen(MatrixXd &&S) override { return 0.0; }
};

class ArithmAsianCall : public PathDepOption {
public:
  double K;
  ArithmAsianCall(double T_, double K_, int m_) : K(K_) {
    T = T_;
    m = m_;
  }
  double Payoff(SamplePath &S) override;
  double PayoffEigen(MatrixXd &&S) override;
};

class EurBasketCall : public PathDepOption {
public:
  double K;
  EurBasketCall(double T_, double K_, int m_) : K(K_) {
    T = T_;
    m = m_;
  }
  double Payoff(SamplePath &S) override;
  double PayoffEigen(MatrixXd &&S) override;
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_PATHDEPENDENTOPTION05_H_
