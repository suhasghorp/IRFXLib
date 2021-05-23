#include "ql.h"
#include <IRFXLib/BinLattice02.h>
#include <IRFXLib/BinModel02.h>
#include <IRFXLib/Options09.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace lecture3;

int main() {

  double S0{}, sigma{}, R{};
  int T{}, N{};
  cout << "Enter Spot: ";
  cin >> S0;
  cout << "Enter Time to Maturity in years: ";
  cin >> T;
  cout << "Enter Volatility (e.g. 0.2): ";
  cin >> sigma;
  cout << "Enter Interest Rate (e.g. 0.05): ";
  cin >> R;
  cout << "Enter Steps to Expiry N: ";
  cin >> N;
  cout << endl;

  lecture2::BinModel Model(S0, R, T, sigma, N);

  Put PutOption(Model.GetN());
  PutOption.GetInputData();
  BinLattice<double> PriceTree;
  BinLattice<bool> StoppingTree;
  double price = PutOption.PriceBySnell(Model, PriceTree, StoppingTree);

  cout << "American Put Price: " << price << endl << endl;

  auto result = PriceByQuantLib(
      ExerciseType::American, OptionType::Put, PayoffType::Vanilla,
      Model.GetS0(), Model.GetR(), Model.GetSigma(), PutOption.GetN(),
      Model.GetT(), PutOption.GetK(), 0.0);
  cout << "American Put Price by QuantLib = " << result.price << endl << endl;

  PriceTree.Display();

  cout << "American Put Exercise Policy: 0 - option should NOT be exercised at "
          "given node"
       << endl
       << endl;
  StoppingTree.Display();

  /*Call Option1(Model.GetN()) ;
  Option1.GetInputData();
  cout << "European Call Option Price = " << Option1.PriceByCRR(Model) << endl;

  auto qlPrice = PriceByQuantLib(
      ExerciseType::European, OptionType::Call, PayoffType::Vanilla,
      Model.GetS0(), Model.GetR(), Model.GetSigma(), Option1.GetN(),
      Model.GetT(), Option1.GetK(), 0.0);
  cout << "European Call Option Price by QuantLib = " << qlPrice.price << endl
  << endl;

  Put Option2(Model.GetN()) ;
  Option2.GetInputData ( ) ;
  cout << "European Put Option Price = " << Option2.PriceByCRR (
  std::move(Model)) << endl;

  qlPrice = PriceByQuantLib(
      ExerciseType::European, OptionType::Put, PayoffType::Vanilla,
      Model.GetS0(), Model.GetR(), Model.GetSigma(), Option1.GetN(),
      Model.GetT(), Option1.GetK(), 0.0);
  cout << "European Put Option Price by QuantLib = " << qlPrice.price << endl <<
  endl;
   */

  return 0;
}
