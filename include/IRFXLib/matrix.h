//
// Created by suhasghorp on 6/2/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_MATRIX_H_
#define IRFXLIB_INCLUDE_IRFXLIB_MATRIX_H_

#include <vector>
using namespace std;
typedef vector<double> Vector;
typedef vector<Vector> Matrix;
Vector operator*(const Matrix &C, const Vector &V);
Vector operator*(const double &a, const Vector &V);
Vector operator+(const double &a, const Vector &V);
Vector operator+(const Vector &V, const Vector &W);
Vector operator*(const Vector &V, const Vector &W);
Vector exp(const Vector &V);
double operator^(const Vector &V, const Vector &W);

#endif // IRFXLIB_INCLUDE_IRFXLIB_MATRIX_H_
