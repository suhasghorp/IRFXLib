//
// Created by suhasghorp on 5/13/2021.
//

#include "IRFXLib/BinModel02.h"

#include <iostream>
#include <cmath>

using namespace std;

namespace lecture2 {

  double BinModel::RiskNeutProb(int N) {

    dt = T / N;
    U = exp(sigma * sqrt(dt));
    D = 1.0 / U;
    return (exp(R * dt) - D) / (U - D);
  }

  double BinModel::S(int n, int i) {
    //return S0 * pow(1+U, i ) * pow(1+D, n - i ) ;
    return S0 * pow(U, i ) * pow(D, n - i ) ;
  }

  int BinModel::GetInputData() {

    cout << "Enter Spot: ";
    cin >> S0;
    cout << "Enter Time to Maturity in years: ";
    cin >> T;
    cout << "Enter Volatility (e.g. 0.2): ";
    cin >> sigma;
    cout << "Enter Interest Rate (e.g. 0.05): ";
    cin >> R;
    cout << endl;

    if (S0 <= 0.0 || U <= -1.0 || D <= -1.0 || U <= D|| R <= -1.0) {
      cout << "Illegal Data Ranges, Terminating program" << endl;
      return 1;
    }

    return 0;
  }

  double BinModel::GetR(){
    return R;
  }

  double BinModel::getDt() { return dt;}
}
