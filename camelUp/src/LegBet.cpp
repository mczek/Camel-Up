#include <Rcpp.h>
#include <stack>
#include "Player.h"
#include "LegBet.h"
using namespace Rcpp;



// Define space class

//' @name LegBet
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export


LegBet::LegBet(std::string color, int v){
  camelColor = color;
  value = v;
}

void LegBet::makeBet(Player * p) {
  person = p;
}


// Approach 4: Module docstrings
//
RCPP_EXPOSED_CLASS(LegBet)
  RCPP_MODULE(legbet_cpp) {
    using namespace Rcpp;

    class_<LegBet>("LegBet")
      .constructor<std::string,int>()
      // .method("makeBet", &LegBet::makeBet)
    ;
  }
