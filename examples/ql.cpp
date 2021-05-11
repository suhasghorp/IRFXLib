
#include <IRFXLib/BinModel01.h>
#include <ql/qldefines.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <iostream>
#include "ql.h"

using namespace QuantLib;
using namespace lecture1;

Result PriceByQuantLib(ExerciseType execType, OptionType optionType, double S0, double R, double sigma, int N, double T, double K){

  Calendar calendar = UnitedStates();
  Date today = Date::todaysDate();
  Date settlementDate = calendar.advance(today, 2, Days);
  Settings::instance().evaluationDate() = today;

  // our options
  Option::Type type((optionType == OptionType::Call) ? Option::Call : Option::Put);
  Real underlying = S0;
  Real strike = K;
  Spread dividendYield = 0.00;
  Rate riskFreeRate = R;
  Size timeSteps = N;
  Volatility volatility = sigma;
  Date maturity = calendar.advance(today, T, Years);
  DayCounter dayCounter = Actual365Fixed();

  ext::shared_ptr<Exercise> exercise;


  ext::shared_ptr<StrikedTypePayoff> payoff(
      new PlainVanillaPayoff(type, strike));

  VanillaOption option(payoff, exercise);

  if (execType == ExerciseType::European) {
    exercise = ext::make_shared<EuropeanExercise>(maturity);
    option = VanillaOption(payoff,exercise);
  } else if (execType == ExerciseType::American) {
    exercise = ext::make_shared<AmericanExercise>(maturity);
    option = VanillaOption(payoff,exercise);
  }
  Handle<Quote> underlyingH(ext::shared_ptr<Quote>(new SimpleQuote(underlying)));

  Handle<YieldTermStructure> flatTermStructure(
      ext::shared_ptr<YieldTermStructure>(
          new FlatForward(settlementDate, riskFreeRate, dayCounter)));
  Handle<YieldTermStructure> flatDividendTS(
      ext::shared_ptr<YieldTermStructure>(
          new FlatForward(settlementDate, dividendYield, dayCounter)));
  Handle<BlackVolTermStructure> flatVolTS(
      ext::shared_ptr<BlackVolTermStructure>(
          new BlackConstantVol(settlementDate, calendar, volatility,
                               dayCounter)));

  ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
      new BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                    flatTermStructure, flatVolTS));

  option.setPricingEngine(ext::shared_ptr<PricingEngine>(
      new BinomialVanillaEngine<JarrowRudd>(bsmProcess,timeSteps)));

  struct Result result;
  result.price = option.NPV();
  result.delta = option.delta();
  result.gamma = option.gamma();
  return result;

}


