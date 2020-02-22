#include <Rcpp.h>
#include "Simulator.h"
#include "Game.h"


using namespace Rcpp;

// Define space class

//' @name Simulator
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export


Simulator::Simulator(Game g){
  Game gameObject = g;
}

DataFrame Simulator::simulateMove(){
  int nCamels = 5;
}


//
RCPP_EXPOSED_CLASS(Simulator)
  RCPP_MODULE(simulator_cpp) {
    using namespace Rcpp;

    class_<Simulator>("Simulator")
      .constructor<Game>()
    ;
  }
