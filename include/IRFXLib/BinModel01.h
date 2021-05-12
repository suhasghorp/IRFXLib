#ifndef BinModel01_h
#define BinModel01_h

namespace lecture1 {

//American or European
enum class ExerciseType { American, European};

enum class OptionType { Call, Put};

enum PayoffType { Vanilla, Digital};

struct Result { double price; double delta; double gamma ;};

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