//
// Created by suhasghorp on 5/13/2021.
//

#ifndef IRFXLIB_SRC_OPTIONS04_H_
#define IRFXLIB_SRC_OPTIONS04_H_

#include <IRFXLib/BinModel02.h>

namespace lecture2 {

int GetInputData(int &N, double &K);

double PriceByCRR(BinModel Model, int N, double K,
                  double (*Payoff)(double z, double K));

double CallPayoff(double z, double K);

double PutPayoff(double z, double K);
} // namespace lecture2

#endif // IRFXLIB_SRC_OPTIONS04_H_
