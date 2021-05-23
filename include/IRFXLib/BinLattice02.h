//
// Created by suhasghorp on 5/21/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_BINLATTICE02_H_
#define IRFXLIB_INCLUDE_IRFXLIB_BINLATTICE02_H_

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

namespace lecture3 {

template <typename Type> class BinLattice {
  ;

private:
  int N;
  vector<vector<Type>> Lattice;

public:
  void SetN(int N_) {
    N = N_;
    Lattice.resize(N + 1);
    for (int i = 0; i <= N; i++) {
      Lattice[i].resize(N + 1);
    }
  }
  void SetNode(int n, int i, Type x) { Lattice[n][i] = x; }
  Type GetNode(int n, int i) { return Lattice[n][i]; }

  void Display() {
    cout << setiosflags(ios::fixed) << setprecision(5);
    for (int n = 0; n <= N; n++) {
      for (int i = 0; i <= n; i++)
        cout << setw(9) << GetNode(n, i);
      cout << endl;
    }
    cout << endl;
  }
};

} // namespace lecture3

#endif // IRFXLIB_INCLUDE_IRFXLIB_BINLATTICE02_H_
