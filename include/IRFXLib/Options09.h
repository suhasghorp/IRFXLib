//
// Created by suhasghorp on 5/22/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_OPTIONS09_H_
#define IRFXLIB_INCLUDE_IRFXLIB_OPTIONS09_H_

#include <IRFXLib/BinLattice02.h>
#include <IRFXLib/BinModel02.h>

namespace lecture3 {

class Option {
private:
  int N;

public:
  explicit Option(int n) : N{n} {}
  void SetN(int N_) { N = N_; }
  int GetN() const { return N; }
  virtual double PayOff(double z) = 0;
};

class EurOption : public virtual Option {
public:
  explicit EurOption(int n) : Option(n) {}
  double PriceByCRR(const lecture2::BinModel &Model);
};

class AmOption : public virtual Option {
public:
  explicit AmOption(int n) : Option(n) {}
  double PriceBySnell(const lecture2::BinModel &Model,
                      lecture3::BinLattice<double> &PriceTree,
                      lecture3::BinLattice<bool> &StoppingTree);
};

class Call : public EurOption, public AmOption {
private:
  double K;

public:
  explicit Call(int n) : EurOption(n), AmOption(n), Option(n) { K = 0.0; }
  void SetK(int K_) { K = K_; }
  int GetInputData();
  double PayOff(double z) override;
  double GetK() const { return K; }
};

class Put : public EurOption, public AmOption {
private:
  double K;

public:
  explicit Put(int n) : EurOption(n), AmOption(n), Option(n) {}
  void SetK(int K_) { K = K_; }
  int GetInputData();
  double PayOff(double z) override;
  double GetK() { return K; }
};

} // namespace lecture3

#endif // IRFXLIB_INCLUDE_IRFXLIB_OPTIONS09_H_
