//
// Created by suhasghorp on 5/13/2021.
//

#ifndef IRFXLIB_SRC_BINMODEL02_H_
#define IRFXLIB_SRC_BINMODEL02_H_

#include <IRFXLib/utils.h>

namespace lecture2 {

  class BinModel {

   private:
    ExerciseType execType;
    OptionType optionType;
    PayoffType payoffType;
    double S0;
    double U;
    double D;
    double R;
    double Q;
    double T;
    double sigma;
    double dt;
    int N;

  public:
    BinModel() = default;
    BinModel(double s_0, double r, double q, double t, double sigma, int n);
    BinModel &operator=(const BinModel &) = default;
    BinModel(const BinModel &) = default;
    BinModel(BinModel &&) noexcept = default;
    BinModel &operator=(BinModel &&) noexcept = default;
    virtual ~BinModel() = default;

    const double RiskNeutProb() const;

    [[nodiscard]] double S(int n, int i) const;

    double GetR() const;

    double GetS0() const;

    double GetT() const;

    int GetN() const;

    double GetQ() const;

    double GetSigma() const;

    double getDt() const;
  };

  BinModel GetInputData();

  } // namespace lecture2

#endif //IRFXLIB_SRC_BINMODEL02_H_
