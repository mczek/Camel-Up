#include <Rcpp.h>
#include <stack>
#include "Space.h"
#include "Camel.h"



// Define space class

//' @name Space
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export


Space::Space(int pos){
  position = pos;
  nCamels = 0;
  plusTile = false;
  minusTile = false;
}

int Space::getPosition() {
  return position;
}

void Space::addCamel(Camel c){
  camels.push(c);
  nCamels += 1;
  c.setHeight(nCamels);
  c.setSpace(position);
}

int Space::getNCamels(){
  return nCamels;
}

Camel Space::removeCamel(){
  Camel result = camels.top();
  camels.pop();
  nCamels -= 1;
  return result;
}

bool Space::getPlusTile(){
  return plusTile;
}

bool Space::getMinusTile(){
  return minusTile;
}


// Approach 4: Module docstrings
//
RCPP_EXPOSED_CLASS(Space)
  RCPP_MODULE(space_cpp) {
    using namespace Rcpp;

    class_<Space>("Space")
      .constructor<int>()
      .method("getPosition", &Space::getPosition)
      .method("getNCamels", &Space::getNCamels)
      .method("getPlusTile", &Space::getPlusTile)
      .method("getMinusTile", &Space::getMinusTile)
    ;
  }
