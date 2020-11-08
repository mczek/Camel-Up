#include <Rcpp.h>
#include "Agent.h"
#include "Game.h"
#include "Board.h"
using namespace Rcpp;
using namespace std;
#include <memory>

// Define agent class



//' @name Agent
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export

Agent::Agent(std::string name){
  name_ = name;
}

std::string Agent::getName(){
  return name_;
}

void Agent::joinGame(Game* g){
  currentGame_ = g;
}

Game Agent::getGame(){
  return *currentGame_;
}

std::string Agent::getRandomChoice(){
  std::vector<std::string> choices = currentGame_->getTurnOptions();
  std::random_shuffle(choices.begin(), choices.end(), randWrapper);// need to shuffle dice
  return choices[0];
}

void Agent::takeTurn(std::string decision){
  if(decision.compare("move") == 0){
    currentGame_->takeTurnMove();
  }

  if(decision.compare("legBetGreen") == 0){
    currentGame_->takeTurnLegBet("Green");
  }

  if(decision.compare("legBetWhite") == 0){
    currentGame_->takeTurnLegBet("White");
  }

  if(decision.compare("legBetYellow") == 0){
    currentGame_->takeTurnLegBet("Yellow");
  }

  if(decision.compare("legBetOrange") == 0){
    currentGame_->takeTurnLegBet("Orange");
  }

  if(decision.compare("legBetGreen") == 0){
    currentGame_->takeTurnLegBet("Green");
  }
}



RCPP_MODULE(agent_cpp){
  using namespace Rcpp;
  class_<Agent>("Agent")
  .constructor<std::string>()
  .method("getName", &Agent::getName)
  .method("joinGame", &Agent::joinGame)
  .method("getGame", &Agent::getGame)
  .method("getRandomChoice", &Agent::getRandomChoice)
  .method("takeTurn", &Agent::takeTurn)
  ;
}
