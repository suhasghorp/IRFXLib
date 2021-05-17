#include <IRFXLib/DoubleDigitalPayoff.h>

Real DoubleDigitalPayoff::operator()(Real price) const {
  return ((strike_ <= price && price <= secondStrike_) ? 1.0 : 0.0);
}