
#include "ql.h"
#include <IRFXLib/BinModel01.h>
#include <IRFXLib/DoubleDigitalPayoff.h>
#include <iostream>
#include <ql/instruments/payoffs.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/analyticdigitalamericanengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/qldefines.hpp>
#include <ql/time/calendars/unitedstates.hpp>

using namespace QuantLib;
using namespace lecture1;

Result PriceByQuantLib(ExerciseType execType, OptionType optionType,
                       PayoffType payoffType, double S0, double R, double Q,
                       double sigma, int N, double T, double K1, double K2) {

  Calendar calendar = UnitedStates();
  Date today = Date::todaysDate();
  Date settlementDate = calendar.advance(today, 2, Days);
  Settings::instance().evaluationDate() = today;

  // our options
  Option::Type type((optionType == OptionType::Call) ? Option::Call
                                                     : Option::Put);
  Real underlying = S0;
  Real strike = K1;
  Real secondStrike = K2;
  Spread dividendYield = Q;
  Rate riskFreeRate = R;
  Size timeSteps = N;
  Volatility volatility = sigma;
  // Date maturity = calendar.advance(today, T, Years);
  Date maturity = calendar.advance(today, Period(6, Months));
  // Date maturity = today + ( T * Years);
  DayCounter dayCounter = Actual365Fixed();

  ext::shared_ptr<Exercise> exercise;
  ext::shared_ptr<StrikedTypePayoff> payoff;
  ext::shared_ptr<PricingEngine> engine;
  VanillaOption option(payoff, exercise);

  Handle<Quote> underlyingH(
      ext::shared_ptr<Quote>(new SimpleQuote(underlying)));

  Handle<YieldTermStructure> flatTermStructure(
      ext::shared_ptr<YieldTermStructure>(
          new FlatForward(settlementDate, riskFreeRate, dayCounter)));
  Handle<YieldTermStructure> flatDividendTS(ext::shared_ptr<YieldTermStructure>(
      new FlatForward(settlementDate, dividendYield, dayCounter)));
  Handle<BlackVolTermStructure> flatVolTS(
      ext::shared_ptr<BlackVolTermStructure>(new BlackConstantVol(
          settlementDate, calendar, volatility, dayCounter)));

  ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
      new BlackScholesMertonProcess(underlyingH, flatDividendTS,
                                    flatTermStructure, flatVolTS));

  if (execType == ExerciseType::European) {
    exercise = ext::make_shared<EuropeanExercise>(maturity);
    if (payoffType == PayoffType::Digital) {
      payoff = ext::make_shared<CashOrNothingPayoff>(type, strike, 1);
      engine = ext::make_shared<AnalyticEuropeanEngine>(bsmProcess);
      option = VanillaOption(payoff, exercise);
      option.setPricingEngine(engine);
    }
    if (payoffType == PayoffType::DDigital) {
      payoff =
          ext::make_shared<DoubleDigitalPayoff>(type, strike, secondStrike);
      /*engine = MakeMCEuropeanEngine<PseudoRandom>(bsmProcess)
        .withSteps(timeSteps)
        .withAbsoluteTolerance(0.02)
        .withSeed(42);*/
      engine = ext::make_shared<FdBlackScholesVanillaEngine>(bsmProcess);
      option = VanillaOption(payoff, exercise);
      option.setPricingEngine(engine);
    } else if (payoffType == PayoffType::Vanilla) {
      payoff = ext::make_shared<PlainVanillaPayoff>(type, strike);
      engine = ext::make_shared<BinomialVanillaEngine<JarrowRudd>>(bsmProcess,
                                                                   timeSteps);
      option = VanillaOption(payoff, exercise);
      option.setPricingEngine(engine);
    }
  } else if (execType == ExerciseType::American) {
    exercise = ext::make_shared<AmericanExercise>(maturity);
    if (payoffType == PayoffType::Digital) {
      payoff = ext::make_shared<CashOrNothingPayoff>(type, strike, 1);
      engine = ext::make_shared<AnalyticDigitalAmericanEngine>(bsmProcess);
      option = VanillaOption(payoff, exercise);
      option.setPricingEngine(engine);
    }
    if (payoffType == PayoffType::DDigital) {
      payoff =
          ext::make_shared<DoubleDigitalPayoff>(type, strike, secondStrike);
      engine = ext::make_shared<AnalyticDigitalAmericanEngine>(bsmProcess);
      option = VanillaOption(payoff, exercise);
      option.setPricingEngine(engine);
    } else if (payoffType == PayoffType::Vanilla) {
      payoff = ext::make_shared<PlainVanillaPayoff>(type, strike);
      engine = ext::make_shared<BinomialVanillaEngine<JarrowRudd>>(bsmProcess,
                                                                   timeSteps);
      option = VanillaOption(payoff, exercise);
      option.setPricingEngine(engine);
    }
  }

  struct Result result {};
  result.price = option.NPV();
  result.delta = option.delta();
  result.gamma = option.gamma();
  return result;
}
