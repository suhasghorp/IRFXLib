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
    int GetN() { return N; }
  };


//double CallPayoff(double z, double K);

class Call : public EurOption { ;
 private:
  double K;
 public:
  void SetK ( double K_ ) {K=K_;}
  int GetInputData ( ) ;
  virtual double Payoff ( double z ) ;
};

class Put: public EurOption {
   private:
    double K;
   public:
    void SetK ( double K_ ) {K=K_;}
    int GetInputData ( ) ;
    virtual double Payoff ( double z ) ;
  };

  class DoubleDigital : public EurOption {
    ;

  private:
    double K1, K2;

  public:
    int GetInputData();
    virtual double Payoff(double z);
    double GetK1() const;
    double GetK2() const;
  };
}
#endif //IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_
