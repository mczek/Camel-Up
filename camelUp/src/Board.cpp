#include <Rcpp.h>
#include <vector>
#include <algorithm>
#include "Space.h"
#include "Board.h"
#include "Camel.h"
using namespace Rcpp;
// Define board class

//' @name Board
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export

Board::Board(int n){
  nSpaces = n;
  for(int i=0;i<n;i++){
    spaces.push_back(Space(i));
  }

  resetDice();
  initCamels();
}

int Board::getNDiceRemaining(){
  return dice.size();
}

void Board::resetDice(){
  dice.push_back(Die("Green"));
  dice.push_back(Die("Yellow"));
  dice.push_back(Die("Orange"));
  dice.push_back(Die("Blue"));
  dice.push_back(Die("White"));

  std::random_shuffle(dice.begin(), dice.end()); //shuffle dice
  // TODO: shuffle dice!
}

void Board::initCamels(){
  int space;
  for(int i=0;i<5;i++){
    Die currentDie = dice[i];
    std::string currentColor = currentDie.getColor();
    space = currentDie.roll();
    Camel currentCamel = Camel(currentColor);
    camels.push_back(currentCamel);

    Space currentSpace = spaces[space];
    currentSpace.addCamel(currentCamel);
  }

}

int Board::getNCamels(){
  return camels.size();
}


RCPP_MODULE(board_cpp){
  class_<Board>("Board")
  .constructor<int>()
  .method("getNDiceRemaining", &Board::getNDiceRemaining)
  .method("getNCamels", &Board::getNCamels)
  ;
}
