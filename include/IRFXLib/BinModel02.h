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
    double T;
    double sigma;
    double dt;

  public:
    double RiskNeutProb(int N);

    [[nodiscard]] double S(int n, int i) const;

    int GetInputData();

    double GetR() const;

    double GetS0() const;

    double GetT() const;

    double GetSigma() const;

    double getDt() const;
  };
}

#endif //IRFXLIB_SRC_BINMODEL02_H_
