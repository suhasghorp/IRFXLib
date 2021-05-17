#include "ql.h"
#include <IRFXLib/BinModel02.h>
#include <IRFXLib/Option06.h>
#include <IRFXLib/Options04.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace lecture2;

int main() {

  BinModel Model;
  if (Model.GetInputData() == 1)
    return 1;

  /*Call Option1 ;
  Option1.GetInputData();
  cout << " European Call Option Price = " << Option1.PriceByCRR ( Model)  <<
  endl << endl;

  Put Option2 ;
  Option2.GetInputData ( ) ;
  cout << " European Put Option Price = " << Option2.PriceByCRR ( Model) << endl
  << endl;*/

  DoubleDigital Option3;
  Option3.GetInputData();
  cout << " Double Digital Option Price by CRR = " << Option3.PriceByCRR(Model)
       << endl
       << endl;

  auto qlPrice = PriceByQuantLib(
      ExerciseType::European, OptionType::Call, PayoffType::DDigital,
      Model.GetS0(), Model.GetR(), Model.GetSigma(), Option3.GetN(),
      Model.GetT(), Option3.GetK1(), Option3.GetK2());
  cout << " Double Digital Option Price by QuantLib = " << qlPrice.price << endl
       << endl;
  return 0;

  /*BinModel Model;

  if (Model.GetInputData() == 1) return 1;
  double K;
  int N;
  cout << " Enter Call Option data : " << endl;

  GetInputData(N, K);
  cout << " European Call Option Price = " << PriceByCRR(Model, N, K,
  CallPayoff) << endl << endl; cout << " Enter Put Option Data : " << endl;
  GetInputData(N, K);
  cout << " European Put Option Price = " << PriceByCRR(Model, N, K, PutPayoff)
  << endl << endl; return 0;*/
}