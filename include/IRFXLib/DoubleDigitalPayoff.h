//
// Created by suhasghorp on 5/16/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_DOUBLEDIGITALPAYOFF_H_
#define IRFXLIB_INCLUDE_IRFXLIB_DOUBLEDIGITALPAYOFF_H_

#include <ql/instruments/payoffs.hpp>
#include <ql/option.hpp>
#include <ql/payoff.hpp>

using namespace QuantLib;

class DoubleDigitalPayoff : public GapPayoff {
public:
  DoubleDigitalPayoff(Option::Type type, Real strike, Real secondStrike)
      : GapPayoff(type, strike, secondStrike) {}
  Real operator()(Real price) const override;
};

#endif // IRFXLIB_INCLUDE_IRFXLIB_DOUBLEDIGITALPAYOFF_H_
