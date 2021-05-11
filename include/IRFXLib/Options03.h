#ifndef Options03_h
#define Options03_h
#include "BinModel01.h"

namespace lecture1 {



// inputting and displaying option data
int GetInputData(int &N, double &K);

// pricing European option
Result PriceByCRR(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K, double (*Payoff)(double z, double K));

// pricing by analytical formula
double PriceByAnalytical(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K, double (*Payoff)(double z, double K));

// pricing by black-scholes
double PriceByBS(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K, double (*Payoff)(double z, double K));

// computing callpayoff
double CallPayoff(double z, double K);

// computing put payoff
double PutPayoff(double z, double K);

// digital call payoff
double DigitalCallPayoff(double z, double K);

// digital put payoff
double DigitalPutPayoff(double z, double K);

//interchange
void interchange ( double& a , double& b );

//sort
void bubblesort( double a[], int N);

} // namespace lecture1

#endif