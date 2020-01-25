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

Board::Board(int n, bool d){
  debug = d;
  nSpaces = n;
  colors = {"Green", "White", "Yellow", "Orange", "Blue"};


  for(int i=0;i<n;i++){
    spaces.push_back(new Space(i));
  }

  resetDice();
  initCamels();
}

int Board::getNDiceRemaining(){
  return dice.size();
}

void Board::resetDice(){ // can't define default arg twice
  int nCamels = colors.size();

  for(int i=0;i<nCamels;i++){
    dice.push_back(colors[i]);
  }

  //shuffle dice
  // this is necessary because R can't set this seed
  if(!debug){
    std::random_shuffle(dice.begin(), dice.end()); //shuffle dice
  }
}

void Board::initCamels(){
  int space;
  for(int i=0;i<5;i++){
    Die currentDie = dice[i];
    std::string currentColor = currentDie.getColor();

    space = currentDie.roll();
    Camel * currentCamel = new Camel(currentColor);
    Space * currentSpace = spaces[space];
    (*currentSpace).addCamel(currentCamel);
    camels[currentColor] = currentCamel;
  }

}

int Board::getNCamels(){
  return camels.size();
}


DataFrame Board::getCamelDF(){
  std::vector<Camel> tempCamels;
  std::vector<std::string> colorsVec;
  std::vector<int> spaceValues, heightValues;
  std::string currentColor;

  int nCamels = colors.size();
  for(int i=0;i<nCamels;i++){
    currentColor = colors[i];
    Camel* currentCamel = camels[currentColor];
    colorsVec.push_back((*currentCamel).getColor());
    spaceValues.push_back((*currentCamel).getSpace());
    heightValues.push_back((*currentCamel).getHeight());
  }

  DataFrame df = DataFrame::create(Named("Color") = colorsVec, Named("Space") = spaceValues, Named("Height") = heightValues);
  return df;

}

// TODO: rewrite this function
int Board::moveTurn(){
  if(dice.size() < 1){
    throw std::range_error("Trying to access dice when leg is over: See Board::moveTurn");
  }

  Die currentDie = dice.back();
  dice.pop_back();
  std::string camelColor = currentDie.getColor();
  int dieValue = currentDie.roll();

  Camel * camelToMove = camels[camelColor];
  int currentSpaceNum = (*camelToMove).getSpace();
  int currentHeight = (*camelToMove).getHeight();

  Space * currentSpace = spaces[currentSpaceNum];
  int currentNCamels = (*currentSpace).getNCamels();

  std::stack<Camel *> temp;

  for(int i=currentHeight; i<=currentNCamels; i++){
    temp.push((*currentSpace).removeCamel());
  }

  Space* newSpace = spaces[currentSpaceNum + dieValue];


  (*newSpace).addCamelsTop(temp);



  // for(int i=currentHeight; i<=currentNCamels; i++){
  //   Camel * c = temp.top();
  //   temp.pop();
  //   (*newSpace).addCamel(c);
  //
  // }


  return temp.size();
}

RCPP_MODULE(board_cpp){
  class_<Board>("Board")
  .constructor<int, bool>()
  .method("getNDiceRemaining", &Board::getNDiceRemaining)
  .method("getNCamels", &Board::getNCamels)
  .method("getCamelDF", &Board::getCamelDF)
  .method("moveTurn", &Board::moveTurn)
  ;
}
