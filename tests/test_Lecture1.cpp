#define CATCH_CONFIG_MAIN
#include <IRFXLib/Options03.h>
#include <IRFXLib/BinModel01.h>
#include <catch.hpp>
#include <spdlog/spdlog.h>
#include <math.h>

/*TEST_CASE("European Call Option Price") {

  SECTION("s0=100,k=100,T=1 year,N=100,sigma=20%,r=0.05") {

    double S0 = 100.0; // spot price, U, D, R;
    double K = 100; // strike price
    double sigma = 0.2;
    //maturity in years
    double T = 1.0;
    //number of steps
    double N = 10000;
    //dt
    double dt = T/N;
    double R = 0.05;
    lecture1::OptionType optionType = lecture1::OptionType::European;

    double CRRPrice = lecture1::PriceByCRR(optionType, S0, R, sigma, N, T, K, lecture1::CallPayoff);
    spdlog::info("European Call Option Price by CRR: {}", CRRPrice);
    double AnalyticalPrice = lecture1::PriceByAnalytical(optionType, S0, R, sigma, N, T, K, lecture1::CallPayoff);
    spdlog::info("European Call Option Price by Analytical: {}", AnalyticalPrice);
    double BSPrice = lecture1::PriceByBS(optionType, S0, R, sigma, N, T, K, lecture1::CallPayoff);
    spdlog::info("European Call Option Price by BS: {}", BSPrice); //10.460001667918041

    REQUIRE(CRRPrice == Approx(10.4306116622));

    REQUIRE(CRRPrice == Approx(AnalyticalPrice));
  }
}

TEST_CASE("European Put Option Price") {
  SECTION("S0=100,K=100,N=100") {
    double S0 = 100.0; // spot price, U, D, R;
    double K = 100; // strike price
    double sigma = 0.2;
    //maturity in years
    double T = 1.0;
    //number of steps
    double N = 100;
    //dt
    double dt = T/N;
    double R = 0.05;
    lecture1::OptionType optionType = lecture1::OptionType::European;

    double CRRPrice = lecture1::PriceByCRR(optionType, S0, R, sigma, N, T, K, lecture1::PutPayoff);
    spdlog::info("European Put Option Price by CRR: {}", CRRPrice);
    double AnalyticalPrice = lecture1::PriceByAnalytical(optionType, S0, R, sigma, N, T, K, lecture1::PutPayoff);
    spdlog::info("European Put Option Price by Analytical: {}", AnalyticalPrice);
    REQUIRE(CRRPrice == Approx(5.5535541123));

    REQUIRE(CRRPrice == Approx(AnalyticalPrice));
  }
}

TEST_CASE("European Digital Call Option Price") {
  SECTION("S0=100,K=100,N=50") {
    double S0 = 100.0; // spot price, U, D, R;
    double K = 100; // strike price
    double sigma = 0.2;
    //maturity in years
    double T = 1.0;
    //number of steps
    double N = 100;
    //dt
    double dt = T/N;
    double R = 0.05;
    lecture1::OptionType optionType = lecture1::OptionType::European;

    double CRRPrice = lecture1::PriceByCRR(optionType, S0, R, sigma, N, T, K, lecture1::DigitalCallPayoff);
    spdlog::info("European Digital Call Option Price by CRR: {}", CRRPrice);
    double AnalyticalPrice = lecture1::PriceByAnalytical(optionType, S0, R, sigma, N, T, K, lecture1::DigitalCallPayoff);
    spdlog::info("European Digital Call Option Price by Analytical: {}", AnalyticalPrice);
    REQUIRE(CRRPrice == Approx(0.5696358654));

    REQUIRE(CRRPrice == Approx(AnalyticalPrice));
  }
}

TEST_CASE("European Digital Put Price") {
  SECTION("S0=100,K=100,N=50") {
    double S0 = 100.0; // spot price, U, D, R;
    double K = 100; // strike price
    double sigma = 0.2;
    //maturity in years
    double T = 1.0;
    //number of steps
    double N = 100;
    //dt
    double dt = T/N;
    double R = 0.05;
    lecture1::OptionType optionType = lecture1::OptionType::Call;
    lecture1::ExerciseType execType = lecture1::ExerciseType::European;

    double CRRPrice = lecture1::PriceByCRR(execType, optionType,S0, R, sigma, N, T, K, lecture1::DigitalPutPayoff);
    spdlog::info("European Digital Put Option Price by CRR: {}", CRRPrice);
    double AnalyticalPrice = lecture1::PriceByAnalytical(optionType,S0, R, sigma, N, T, K, lecture1::DigitalPutPayoff);
    spdlog::info("European Digital Put Option Price by Analytical: {}", AnalyticalPrice);
    REQUIRE(CRRPrice == Approx(0.3815935590));
    REQUIRE(CRRPrice == Approx(AnalyticalPrice));
  }
}*/

TEST_CASE("Interchange") {
  double a = 10;
  double b = 20;
  spdlog::info("a and b before interchange: {} , {}", a, b);
  lecture1::interchange(a, b);
  spdlog::info("a and b after interchange: {} , {}", a, b);
}

void printArray(double arr[], int size) {
  using namespace std;
  int i;
  for (i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

TEST_CASE("Bubblesort") {
  double arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr) / sizeof(arr[0]);
  spdlog::info("Array before bubblesort");
  printArray(arr, n);
  lecture1::bubblesort(arr, n);
  spdlog::info("Array after bubblesort");
  printArray(arr, n);
}
