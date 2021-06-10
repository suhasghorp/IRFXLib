#include <IRFXLib/CVEurBasketCall.h>
#include <IRFXLib/EurCall.h>
#include <IRFXLib/PathDependentOption05.h>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  int d = 3;
  double r = 0.03;
  Vector S0(d);
  S0[0] = 40.0;
  S0[1] = 60.0;
  S0[2] = 100.0;

  Matrix C(d);
  for (int i = 0; i < d; i++)
    C[i].resize(d);
  C[0][0] = 0.1;
  C[0][1] = -0.1;
  C[0][2] = 0.0;
  C[1][0] = -0.1;
  C[1][1] = 0.2;
  C[1][2] = 0.0;
  C[2][0] = 0.0;
  C[2][1] = 0.0;
  C[2][2] = 0.3;

  VectorXd S0Eigen(3);
  S0Eigen << 40.0, 60.0, 100.0;
  MatrixXd CEigen(3, 3);
  CEigen << 0.1, -0.1, 0.0, 0.1, 0.2, 0.0, 0.0, 0.0, 0.3;

  double T = 1.0 / 12.0, K = 200.0;
  int m = 30;
  long N = 30000;

  BSModel Model(S0, r, C);
  ArithmAsianCall Option(T, K, m);
  cout << " Arithmetic Basket Call Price = " << Option.PriceByMC(Model, N)
       << endl;

  BSModelEigen ModelEigen(std::move(S0Eigen), r, std::move(CEigen));
  ArithmAsianCall OptionEigen(T, K, m);
  cout << " Arithmetic Basket Call Price using Eigen = "
       << OptionEigen.PriceByMCEigen(std::move(ModelEigen), N) << endl;

  EurBasketCall EurBasketOption(T, K, m);
  CVEurBasketCall CVOption(T, K, m);
  cout << " Homework 4.1 - Crude European Basket Call Price = "
       << EurBasketOption.PriceByMC(Model, N) << endl
       << " Error = " << EurBasketOption.PricingError << endl;

  // EurBasketOption.PriceByVarRedMC ( Model ,N, CVOption ) ;
  DifferenceOfOptions VarRedOpt(T, m, &EurBasketOption, &CVOption);
  double Price = VarRedOpt.PriceByMC(Model, N);
  vector<double> sigma;
  double BSPrice = 0.0;
  sigma.push_back(sqrt(pow(C[0][0], 2) + pow(C[0][1], 2) + pow(C[0][2], 2)));
  sigma.push_back(sqrt(pow(C[1][0], 2) + pow(C[1][1], 2) + pow(C[1][2], 2)));
  sigma.push_back(sqrt(pow(C[2][0], 2) + pow(C[2][1], 2) + pow(C[2][2], 2)));
  for (int i = 0; i < C[0].size(); i++) {
    double K0 = K * (S0[i] / (S0[0] + S0[1] + S0[2]));
    EurCall G(T, K0);
    BSPrice += G.PriceByBSFormula(S0[i], sigma[i], r);
  }
  Price += BSPrice;
  double PricingError = VarRedOpt.PricingError;
  cout << " Homework 4.1 - Control Variate European Basket call price = "
       << Price << endl
       << " Error = " << PricingError << endl;
  return 0;
}