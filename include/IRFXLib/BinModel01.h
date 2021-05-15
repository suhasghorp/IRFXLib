#ifndef BinModel01_h
#define BinModel01_h

#include <IRFXLib/utils.h>
namespace lecture1 {

// computing risk neutral probability
double RiskNeutProb(double U, double D, double R);

double RiskNeutProbBS(double U, double D, double R);

// computing the stock price at node (n,i)
double S(double S0, double U, double D, int n, int i);

// computing the stock price at node (n,i)
double S_BS(double S0, double U, double D, int n, int i);

// inputting, displaying and checking data
int GetInputData(double &S0, double &U, double &D, double &R);

// inputting, displaying and checking data
int GetInputData2(ExerciseType& execType, OptionType& optionType, PayoffType& payoffType, double &S0, double &K, double &T, int &N, double &sigma, double &R);

} // namespace lecture1

#endif