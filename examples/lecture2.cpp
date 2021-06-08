#include "ql.h"
#include <IRFXLib/BinModel02.h>
#include <IRFXLib/Option06.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace lecture2;

int main() {

  BinModel Model = GetInputData();

  Call Option1(Model.GetN());
  Option1.GetInputData();
  cout << "European Call Option Price = "
       << Option1.PriceByCRR(std::move(Model)) << endl;

  auto qlPrice = PriceByQuantLib(
      ExerciseType::European, OptionType::Call, PayoffType::Vanilla,
      Model.GetS0(), Model.GetR(), 0.0, Model.GetSigma(), Option1.GetN(),
      Model.GetT(), Option1.GetK(), 0.0);
  cout << "European Call Option Price by QuantLib = " << qlPrice.price << endl
       << endl;

  Put Option2(Model.GetN());
  Option2.GetInputData();
  cout << "European Put Option Price = " << Option2.PriceByCRR(std::move(Model))
       << endl;

  qlPrice = PriceByQuantLib(ExerciseType::European, OptionType::Put,
                            PayoffType::Vanilla, Model.GetS0(), Model.GetR(),
                            0.0, Model.GetSigma(), Option1.GetN(), Model.GetT(),
                            Option1.GetK(), 0.0);
  cout << "European Put Option Price by QuantLib = " << qlPrice.price << endl
       << endl;

  lecture2::Digital Option4(Model.GetN());
  Option4.GetInputData();
  cout << "Digital Option Price by CRR = "
       << Option4.PriceByCRR(std::move(Model)) << endl;

  qlPrice = PriceByQuantLib(ExerciseType::European, OptionType::Call,
                            PayoffType::Digital, Model.GetS0(), Model.GetR(),
                            0.0, Model.GetSigma(), Option4.GetN(), Model.GetT(),
                            Option4.GetK(), 0.0);
  cout << "Digital Option Price by QuantLib = " << qlPrice.price << endl
       << endl;

  DoubleDigital Option3(Model.GetN());
  Option3.GetInputData();
  cout << "Double Digital Option Price by CRR = "
       << Option3.PriceByCRR(std::move(Model)) << endl;

  qlPrice = PriceByQuantLib(ExerciseType::European, OptionType::Call,
                            PayoffType::DDigital, Model.GetS0(), Model.GetR(),
                            0.0, Model.GetSigma(), Option3.GetN(), Model.GetT(),
                            Option3.GetK1(), Option3.GetK2());
  cout << "Double Digital Option Price by QuantLib = " << qlPrice.price << endl
       << endl;

  return 0;
}
