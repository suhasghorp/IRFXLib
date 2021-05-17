//
// Created by suhasghorp on 5/11/2021.
//

#ifndef IRFXLIB_EXAMPLES_QL_H_
#define IRFXLIB_EXAMPLES_QL_H_

#include <IRFXLib/BinModel01.h>
using namespace lecture1;
Result PriceByQuantLib(ExerciseType execType, OptionType optionType,
                       PayoffType payoffType, double S0, double R, double sigma,
                       int N, double T, double K1, double K2);

//Result PriceBinaryByQuantLib(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K);


#endif //IRFXLIB_EXAMPLES_QL_H_
