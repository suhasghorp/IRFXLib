//
// Created by suhasghorp on 5/13/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_
#define IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_

#include <IRFXLib/BinModel02.h>

namespace lecture2 {
  class EurOption { ;
   private:
    int N;

   public:
    void SetN(int N_) { N = N_; }
    virtual double Payoff (double z) { return 0.0;}
    double PriceByCRR(BinModel Model);
    int GetN() const { return N; }
  };


class Call : public EurOption { ;
 private:
  double K;
 public:
  void SetK ( double K_ ) {K=K_;}
  int GetInputData();
  double Payoff(double z) override;
};

class Put: public EurOption {
   private:
    double K;
   public:
    void SetK ( double K_ ) {K=K_;}
    int GetInputData();
    double Payoff(double z) override;
};

  class DoubleDigital : public EurOption {
  private:
    double K1, K2;

  public:
    int GetInputData();
    double Payoff(double z) override;
    double GetK1() const;
    double GetK2() const;
  };
}
#endif //IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_
