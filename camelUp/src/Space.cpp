#include <Rcpp.h>
#include <stack>
#include "Space.h"
#include "Camel.h"
using namespace Rcpp;



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

Space::Space(){}

Space::Space(int pos){
  position = pos;
  nCamels = 0;
  plusTile = false;
  minusTile = false;
}

int Space::getPosition() {
  return position;
}

void Space::addCamel(Camel * c){
  camels.push(c);
  nCamels += 1;
  (*c).setHeight(nCamels);
  (*c).setSpace(position);
}

int Space::getNCamels(){
  return nCamels;
}

Camel * Space::removeCamel(){
  Camel * result = camels.top();
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

// void Space::addCamelsTop(std::stack<Camel> moveCamels){
//   int nMoveCamels = moveCamels.size();
//   for(int i=0;i<nMoveCamels;i++){
//     Camel & currentCamel = moveCamels.top();
//     moveCamels.pop();
//     addCamel(currentCamel);
//   }
// }
//
// void Space::addCamelsBottom(std::stack<Camel> moveCamels){
//   Camel currentCamel;
//   std::stack<Camel> temp;
//
//   for(int i=0;i<nCamels;i++){
//     currentCamel = removeCamel();
//     temp.push(currentCamel);
//   }
//
//   int nMoveCamels = moveCamels.size();
//   for(int i=0;i<nMoveCamels;i++){
//     currentCamel = moveCamels.top();
//     moveCamels.pop();
//     addCamel(currentCamel);
//   }
//
//   int n = temp.size();
//   for(int i=0;i<n;i++){
//     currentCamel = temp.top();
//     temp.pop();
//     addCamel(currentCamel);
//   }
// }

// int Space::testAddCamel(){
//   Camel b = Camel("Blue");
//   Camel g = Camel("Green");
//   addCamel(b);
//   addCamel(g);
//   // result.push_back(g.getColor());
//
//   return g.getHeight();
// }

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
      // .method("testAddCamel", &Space::testAddCamel)
    ;
  }
