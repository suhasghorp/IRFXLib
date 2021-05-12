#include <IRFXLib/BinModel01.h>
#include <cmath>
#include <iostream>

using namespace std;

namespace lecture1 {

double RiskNeutProb(double U, double D, double R) { return (R - D) / (U - D); }

double RiskNeutProbBS(double U, double D, double R) { return (R - 1.0 - D) / (U - D); }

double S(double S0, double U, double D, int n, int i) {
  //return S0 * pow(1 + U, i) * pow(1 + D, n - i);
  return S0 * pow(U, i) * pow(D, n - i);
}

// computing the stock price at node (n,i)
double S_BS(double S0, double U, double D, int n, int i){
  return S0 * pow(1 + U, i) * pow(1 + D, n - i);
}

int GetInputData2(ExerciseType& execType, OptionType& optionType, PayoffType& payoffType, double &S0, double &K, double &T, int &N, double &sigma, double &R){
  string exec, opt, payoff;

  cout << "Enter Exercise Type (e.g. A or E): ";
  cin >> exec;

  cout << "Enter Option Type (e.g. call or put): ";
  cin >> opt;

  cout << "Enter Payoff Type (e.g. V or D): ";
  cin >> payoff;

  cout << "Enter Spot: ";
  cin >> S0;
  cout << "Enter Strike: ";
  cin >> K;
  cout << "Enter Time to Maturity in years: ";
  cin >> T;
  cout << "Enter Number of Steps: ";
  cin >> N;
  cout << "Enter Volatility (e.g. 0.2): ";
  cin >> sigma;
  cout << "Enter Interest Rate (e.g. 0.05): ";
  cin >> R;
  cout << endl;

  execType = (exec == "A") ? (ExerciseType::American) : (ExerciseType::European);
  optionType = (opt == "call") ? (OptionType::Call) : (OptionType::Put);
  payoffType = (payoff == "V") ? (PayoffType::Vanilla) : (PayoffType::Digital);

  if (S0 <= 0 || K <= 0 || T <= 0 || N <= 0 || sigma <= 0 || R <= 0){
    cout << "Invalid data" << endl;
    return 1;
  }
  return 0;
}

int GetInputData(double &S0, double &U, double &D, double &R) {

  cout << "Enter S0: ";
  cin >> S0;
  cout << "Enter U: ";
  cin >> U;
  cout << "Enter D: ";
  cin >> D;
  cout << "Enter R: ";
  cin >> R;
  cout << endl;

  // making sure that 0 < S0 , -1 < D < U, -1 < R
  if (S0 <= 0.0 || U <= -1.0 || D <= -1.0 || U <= D || R <= -1.0) {

    cout << " Illegal Data Ranges " << endl;
    cout << " Terminating program " << endl;
    return 1;
  }
  // checking for arbitrage
  if (R >= U || R <= D) {
    cout << " Arbitrage Exists " << endl;
    cout << " Terminating program " << endl;
    return 1;
  }
  cout << " Input data checked " << endl;
  cout << " There is no arbitrage " << endl << endl;
  return 0;
}

} // namespace lecture1