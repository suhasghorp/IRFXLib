#include <IRFXLib/Options03.h>
#include <iostream>
#include "ql.h"


using namespace std;
using namespace lecture1;


int main() {
  double S0, K, T, sigma, R;
  int N;
  ExerciseType execType;
  OptionType optionType;
  if (GetInputData2(execType, optionType, S0, K, T, N, sigma, R) == 1) return 1;
  string exec_type, option_type;

  if (execType == ExerciseType::European){
    exec_type = "European";
  } else exec_type = "American";

  if (optionType == OptionType::Call){
    option_type = "Call";
  } else option_type = "Put";


  Result result = PriceByCRR(execType, optionType, S0, R, sigma, N, T, K, optionType == OptionType::Call?CallPayoff : PutPayoff);
  cout << exec_type << " " << option_type << " option price by CRR = "
       <<  result.price << " delta " << result.delta << " gamma " << result.gamma << endl
       << endl;

  result = PriceByQuantLib(execType, optionType, S0, R, sigma, N, T, K);
  cout << exec_type << " " << option_type << " option price by QuantLib = "
       <<  result.price << " delta " << result.delta << " gamma " << result.gamma << endl
       << endl;

  if (execType == ExerciseType::American){
    cout << "I do not know how to handle American type with Analytical solution\n" << endl;
  } else {
    cout << exec_type << " " << option_type << " option price by Analytical = "
         << PriceByAnalytical(execType, optionType, S0, R, sigma, N, T, K, optionType == OptionType::Call?CallPayoff : PutPayoff) << endl
         << endl;
  }

  cout << exec_type << " " << option_type << " option price by Black-Scholes = "
       << PriceByBS(execType, optionType, S0, R, sigma, N, T, K, optionType == OptionType::Call?CallPayoff : PutPayoff) << endl
       << endl;


  /*cout << " European put option price by CRR = "
       << PriceByCRR(optionType, S0, R, sigma,N, T, K, PutPayoff) << endl
       << endl;
  cout << " European put option price by Analytical = "
       << PriceByAnalytical(optionType, S0, R, sigma,N, T, K, PutPayoff) << endl
       << endl;
  cout << " European put option price by Black-Scholes = "
       << PriceByBS(optionType, S0, R, sigma,N, T, K, PutPayoff) << endl
       << endl;*/


  result = PriceByCRR(execType, optionType, S0, R, sigma,N, T, K, optionType == OptionType::Call?DigitalCallPayoff : DigitalPutPayoff);
  cout << exec_type << " Digital " << option_type << " option price by CRR= "
       << result.price << " delta " << result.delta << " gamma " << result.gamma << endl
       << endl;
  cout << exec_type << " Digital " << option_type << " option price by Analytical = "
       << PriceByAnalytical(execType, optionType, S0, R, sigma,N, T, K, optionType == OptionType::Call?DigitalCallPayoff : DigitalPutPayoff) << endl
       << endl;
  cout << exec_type << " Digital " << option_type << " option price by Black-Scholes = "
       << PriceByBS(execType, optionType, S0, R, sigma,N, T, K, optionType == OptionType::Call?DigitalCallPayoff : DigitalPutPayoff) << endl
       << endl;




  return 0;
}

