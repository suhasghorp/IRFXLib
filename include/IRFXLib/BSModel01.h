//
// Created by suhasghorp on 5/28/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_BSMODEL01_H_
#define IRFXLIB_INCLUDE_IRFXLIB_BSMODEL01_H_

#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

typedef vector<double> SamplePath;

class BSModel {
public:
  double S0;
  double r;
  double sigma;

  BSModel(double S0_, double r_, double sigma_)
      : S0(S0_), r(r_), sigma(sigma_) {
    srand(time(NULL));
  }
  void GenerateSamplePath(double T, int m, SamplePath &S);
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_BSMODEL01_H_
