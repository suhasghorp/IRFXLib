//
// Created by suhasghorp on 6/3/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_CVEURBASKETCALL_H_
#define IRFXLIB_INCLUDE_IRFXLIB_CVEURBASKETCALL_H_
#include <IRFXLib/PathDependentOption05.h>

class CVEurBasketCall : public PathDepOption {
public:
  double K;
  CVEurBasketCall(double T_, double K_, int m_) {
    T = T_;
    K = K_;
    m = m_;
  }
  double Payoff(SamplePath &S);
  double PriceByBSFormula(BSModel Model);
  double PayoffEigen(MatrixXd &&S) override;
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_CVEURBASKETCALL_H_
