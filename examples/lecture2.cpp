#include <IRFXLib/BinModel02.h>
#include <IRFXLib/Options04.h>
#include <IRFXLib/Option06.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace lecture2;

int main() {

  BinModel Model ;
  if ( Model.GetInputData ()==1) return 1 ;

  /*Call Option1 ;
  Option1.GetInputData();
  cout << " European Call Option Price = " << Option1.PriceByCRR ( Model)  << endl << endl;

  Put Option2 ;
  Option2.GetInputData ( ) ;
  cout << " European Put Option Price = " << Option2.PriceByCRR ( Model) << endl << endl;*/

  DoubleDigital Option3 ;
  Option3.GetInputData ( ) ;
  cout << " Double Digital Option Price = " << Option3.PriceByCRR ( Model) << endl << endl;

  return 0 ;

  /*BinModel Model;

  if (Model.GetInputData() == 1) return 1;
  double K;
  int N;
  cout << " Enter Call Option data : " << endl;

  GetInputData(N, K);
  cout << " European Call Option Price = " << PriceByCRR(Model, N, K, CallPayoff) << endl << endl;
  cout << " Enter Put Option Data : " << endl;
  GetInputData(N, K);
  cout << " European Put Option Price = " << PriceByCRR(Model, N, K, PutPayoff) << endl << endl;
  return 0;*/
}
