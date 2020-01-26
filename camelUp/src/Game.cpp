#include <Rcpp.h>
#include <stack>
#include "Player.h"
#include "Board.h"
#include "LegBet.h"
#include "Game.h"

using namespace Rcpp;

// Define space class

//' @name Game
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export


Game::Game(int nSpaces, int nPlayers, bool d){
  colors = {"Green", "White", "Yellow", "Orange", "Blue"};
  board = new Board(nSpaces, d);

  for(int i=0;i<nPlayers;i++){
    players.push_back(new Player("Player " + toString(i)));
  }

  currentPlayerIndex = 0;
  resetLegBets();
}

DataFrame Game::getPurseDF(){
  std::vector<std::string> names;
  std::vector<int> purseValues;

  int nPlayers = players.size();
  for(int i=0;i<nPlayers;i++){
    Player* currentPlayer = players[i];
    names.push_back((*currentPlayer).getName());
    purseValues.push_back((*currentPlayer).getCoins());
  }

  DataFrame df = DataFrame::create(Named("Player") = names, Named("Coins") = purseValues);
  return df;
}

DataFrame Game::getCamelDF(){
  return (*board).getCamelDF();
}

std::vector<std::string> Game::getRanking(){
  return (*board).getRanking();
}

std::string Game::takeTurnMove(){
  Player* currentPlayer = players[currentPlayerIndex];
  std::string result = (*board).moveTurn();

  (*currentPlayer).addCoins(1);

  // check for end game and end leg - write function for this
  return result;
}

void Game::resetLegBets(){
  std::vector<int> betValues = {2, 3, 5};
  int nLegBets = betValues.size();

  int nColors = colors.size();
  std::string currentColor;
  for(int i=0; i<nColors; i++){
    currentColor = colors[i];
    // std::stack<LegBet*> tempStack;
    std::stack<LegBet*> betStack;
    for(int j=0; j<nLegBets; j++){
      betStack.push(new LegBet(currentColor, betValues[j]));
    }
    // std::stack<LegBet*>* betStack = * tempStack;
    legBets[currentColor] = betStack; // & gets address of object
  }
}


DataFrame Game::getLegBetDF(){
  // std::vector<std::string> camelColors;
  std::vector<int> nextBetValues;
  std::vector<int> nBetsLeft;

  int nColors = colors.size();
  for(int i=0;i<nColors;i++){
    std::string currentColor = colors[i];
    std::stack<LegBet*> s = legBets[currentColor];

    LegBet* nextBet = s.top();
    nextBetValues.push_back((*nextBet).getValue());
    nBetsLeft.push_back(s.size());
  }

  DataFrame df = DataFrame::create(Named("Color") = colors, Named("Value") = nextBetValues);
  return df;
}

void Game::takeTurnLegBet(std::string camelColor){
  Player* currentPlayer = players[currentPlayerIndex];

  std::stack<LegBet*> colorStack = legBets[camelColor];
  LegBet* betToMake = colorStack.top();
  colorStack.pop();
  (*betToMake).makeBet(currentPlayer);
  madeLegBets.push_back(betToMake);
}

// Approach 4: Module docstrings
//
RCPP_EXPOSED_CLASS(Game)
  RCPP_MODULE(game_cpp) {
    using namespace Rcpp;

    class_<Game>("Game")
      .constructor<int, int, bool>()
      .method("getPurseDF", &Game::getPurseDF)
      .method("getCamelDF", &Game::getCamelDF)
      .method("getRanking", &Game::getRanking)
      .method("takeTurnMove", &Game::takeTurnMove)
      .method("getLegBetDF", &Game::getLegBetDF)
      .method("takeTurnLegBet", &Game::takeTurnLegBet)
    ;
  }
