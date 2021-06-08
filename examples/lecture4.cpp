//
// Created by suhasghorp on 5/29/2021.
//

#include <IRFXLib/GmtrAsianCall.h>
#include <IRFXLib/PathDependentOption01.h>
#include <iostream>
using namespace std;
int main() {
  double S0 = 100.0, r = 0.03, sigma = 0.2;
  BSModel Model(S0, r, sigma);
  double T = 1.0 / 12.0, K = 100.0; // Expiry is 1 month .
  int m = 30;                       // Daily observations for one month !
  ArithmAsianCall Option(T, K, m);
  GmtrAsianCall CVOption(T, K, m);
  long N = 30000;
  // double eps = 0.00001;
  // cout << " Asian Call Price = " << Option.PriceByMC ( Model ,N, eps) << endl
  // ;

  Option.PriceByVarRedMC(Model, N, CVOption);
  cout << " Arithmetic call price = " << Option.Price << endl
       << " Error = " << Option.PricingError << endl;
  Option.PriceByMC(Model, N);
  cout << " Price by direct MC = " << Option.Price << endl
       << "MC Error = " << Option.PricingError << endl;
  return 0;
}
