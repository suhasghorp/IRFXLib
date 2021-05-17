#include <IRFXLib/Options03.h>
#include <iostream>
#include "ql.h"


using namespace std;
using namespace lecture1;


int main() {
  double S0, K, K2, T, sigma, R;
  int N;
  ExerciseType execType;
  OptionType optionType;
  PayoffType payoffType;
  if (GetInputData2(execType, optionType, payoffType, S0, K, K2, T, N, sigma,
                    R) == 1)
    return 1;
  string exec_type, option_type;

  if (execType == ExerciseType::European){
    exec_type = "European";
  } else exec_type = "American";

  if (optionType == OptionType::Call){
    option_type = "Call";
  } else option_type = "Put";

  if (payoffType == PayoffType::Vanilla) {
    Result result = PriceByCRR(execType, optionType, payoffType, S0, R, sigma, N, T, K, optionType == OptionType::Call ? CallPayoff : PutPayoff);
    cout << exec_type << " " << option_type << " option price by CRR = "
         << result.price << " delta " << result.delta << " gamma " << result.gamma << endl
         << endl;

    result = PriceByQuantLib(execType, optionType, payoffType, S0, R, sigma, N,
                             T, K, K2);
    cout << exec_type << " " << option_type
         << " option price by QuantLib = " << result.price << " delta "
         << result.delta << " gamma " << result.gamma << endl
         << endl;

    if (execType == ExerciseType::American) {
      cout << "I do not know how to handle American type with Analytical solution\n" << endl;
    } else {
      cout << exec_type << " " << option_type << " option price by Analytical = "
           << PriceByAnalytical(execType, optionType, payoffType, S0, R, sigma, N, T, K, optionType == OptionType::Call ? CallPayoff : PutPayoff) << endl
           << endl;
    }

    cout << exec_type << " " << option_type << " option price by Black-Scholes = "
         << PriceByBS(execType, optionType, payoffType, S0, R, sigma, N, T, K, optionType == OptionType::Call ? CallPayoff : PutPayoff) << endl
         << endl;

  } else if (payoffType == PayoffType::Digital) {

    Result result = PriceByCRR(execType, optionType, payoffType, S0, R, sigma, N, T, K, optionType == OptionType::Call ? DigitalCallPayoff : DigitalPutPayoff);
    cout << exec_type << " Digital " << option_type << " option price by CRR = "
         << result.price << " delta " << result.delta << " gamma " << result.gamma << endl
         << endl;

    result = PriceByQuantLib(execType, optionType, payoffType, S0, R, sigma, N,
                             T, K, K2);
    cout << exec_type << " Digital " << option_type
         << " option price by QuantLib = " << result.price << " delta "
         << result.delta << " gamma " << result.gamma << endl
         << endl;

    if (execType == ExerciseType::American) {
      cout << "I do not know how to handle American type with Analytical solution\n" << endl;
    } else {
      cout << exec_type << " Digital " << option_type << " option price by Analytical = "
           << PriceByAnalytical(execType, optionType, payoffType, S0, R, sigma, N, T, K, optionType == OptionType::Call ? DigitalCallPayoff : DigitalPutPayoff) << endl
           << endl;
    }
    cout << exec_type << " Digital " << option_type << " option price by Black-Scholes = "
         << PriceByBS(execType, optionType, payoffType, S0, R, sigma, N, T, K, optionType == OptionType::Call ? DigitalCallPayoff : DigitalPutPayoff) << endl
         << endl;
  }




  return 0;
}

