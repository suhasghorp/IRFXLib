//
// Created by suhasghorp on 5/13/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_
#define IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_

#include <IRFXLib/BinModel02.h>

namespace lecture2 {
class EurOption {
  ;

private:
  int N{};

public:
  EurOption() = default;
  explicit EurOption(int n) : N{n} {}
  void SetN(int N_) { N = N_; }
  virtual double Payoff(double z) { return 0.0; }
  double PriceByCRR(const BinModel &Model);
  int GetN() const { return N; }
};

class Call : public EurOption {
  ;

private:
  double K{};

public:
  explicit Call(int n) : EurOption(n) {}
  void SetK(double K_) { K = K_; }
  int GetInputData();
  double GetK() const;
  double Payoff(double z) override;
};

class Put : public EurOption {
private:
  double K{};

public:
  explicit Put(int n) : EurOption(n) {}
  void SetK(double K_) { K = K_; }
  int GetInputData();
  double GetK() const;
  double Payoff(double z) override;
};

class Digital : public EurOption {
private:
  double K{};

public:
  explicit Digital(int n) : EurOption(n) {}
  void SetK(double K_) { K = K_; }
  int GetInputData();
  double GetK() const;
  double Payoff(double z) override;
};

class DoubleDigital : public EurOption {
private:
  double K1{}, K2{};

public:
  explicit DoubleDigital(int n) : EurOption(n) {}
  int GetInputData();
  double Payoff(double z) override;
  double GetK1() const;
  double GetK2() const;
};
} // namespace lecture2
#endif // IRFXLIB_INCLUDE_IRFXLIB_OPTION06_H_
