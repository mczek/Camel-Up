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


Game::Game(int n, int nPlayers, bool d){
  nSpaces = n;
  debug = d;
  isGameOver = false;
  colors = {"Green", "White", "Yellow", "Orange", "Blue"};
  board = new Board(nSpaces, d);

  for(int i=0;i<nPlayers;i++){
    players.push_back(new Player("Player " + toString(i)));
  }

  currentPlayerIndex = 0;
  resetLegBets();
  getRanking();
}

Game::Game(const Game & g){
  //    g.board;
  //    g.colors;
  //    g.currentPlayerIndex;
  //    g.isGameOver;
  // g.legBets;
  // g.madeLegBets;
  //    g.players;
  //    g.rankings; can do at the end

  // currentPlayerIndex = g.currentPlayerIndex;
  // isGameOver = g.isGameOver;
  // colors = {"Green", "White", "Yellow", "Orange", "Blue"};
  //
  // copy player objects
  // int nPlayers = g.players.size();
  // for(int i=0;i<nPlayers;i++){
  //   players.push_back(new Player("Player " + toString(i)));
  // }
  // //
  // board = new Board(g.nSpaces, g.debug);
  // Board* oldBoard = g.board;
  // for(int i=0; i<nSpaces; i++){
  //   Space* oldSpace = (*oldBoard).getSpaceN(i);
  //   Space* newSpace = (*board).getSpaceN(i);
  //
    // tiles
    // Player* currentP;
    // if((*oldSpace).getPlusTile() || (*oldSpace).getMinusTile()){
    //   Player* p = (*oldSpace).getTilePlacedBy();
    //   std::string name = (*p).getName();
    //
    //   int iter = 0;
    //   currentP = players[iter];
    //   while((*currentP).getName() != name){
    //
    //     Player* currentP = players[iter];
    //     iter ++;
    //   }
    // }
    // if((*oldSpace).getPlusTile()){
    //   (*newSpace).setPlusTile(currentP);
    // }
    // if((*oldSpace).getMinusTile()){
    //   (*newSpace).setMinusTile(currentP);
    // }

    //  camel stack
    // int nCamelsHere = (*oldSpace).getNCamels();
    // std::stack<std::string> temp;
    // std::string currentColor;
    // for(int j=0; j<nCamelsHere; j++){
    //   Camel * c = (*oldSpace).removeCamel();
    //   currentColor = (*c).getColor();
    //   Camel * newCamel = (*board).getCamel(currentColor);
    //   (*newSpace).addCamel(newCamel);
    // }
  // }
  //
  // std::vector<Die> oldDice = (*oldBoard).getDice();
  // int nDice = oldDice.size();
  // std::vector<Die> newDice;
  // // this will reverse the order of the dice
  // for(int i=0; i<nDice; i++){
  //   Die d = oldDice[i];
  //   newDice.push_back(d);
  // }
  // (*board).setDice(newDice);
  //
  // // match leg bets
  // resetLegBets();
  // int nColors = colors.size();
  // std::string s;
  // std::stack<LegBet*> oldBetStack;
  // for(int i=0; i<nColors; i++){
  //   s = colors[i];
  //   oldBetStack = g.legBets[s];
  //   int nOldBets = oldBetStack.size();
  //   newBetStack = legBets[s];
  //   int diff = 3-nOldBets;
  //   for(int j=0; j<diff; j++){
  //     newBetStack.pop();
  //   }
  // }

  // getRanking();
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
  rankings = (*board).getRanking();
  return rankings;
}

std::string Game::takeTurnMove(){
  Player* currentPlayer = players[currentPlayerIndex];
  std::string result = (*board).moveTurn();

  (*currentPlayer).addCoins(1);

  endTurn();
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
    std::stack<LegBet*>* s = &legBets[currentColor];

    LegBet* nextBet = (*s).top();
    nextBetValues.push_back((*nextBet).getValue());
    nBetsLeft.push_back((*s).size());
  }

  DataFrame df = DataFrame::create(Named("Color") = colors, Named("Value") = nextBetValues, Named("nBets") = nBetsLeft);
  return df;
}

void Game::takeTurnLegBet(std::string camelColor){
  Player* currentPlayer = players[currentPlayerIndex];

  std::stack<LegBet*>* colorStack = &legBets[camelColor];
  LegBet* betToMake = (*colorStack).top();
  (*colorStack).pop();
  (*betToMake).makeBet(currentPlayer);
  madeLegBets.push_back(betToMake);
}

int Game::getNMadeLegBets(){
  return madeLegBets.size();
}

void Game::evaluateLegBets(){
  // Player* cp = players[0];
  // (*cp).addCoins(21);
  int nBets = madeLegBets.size();
  for(int i=0; i<nBets; i++){
    LegBet* currentBet = madeLegBets[i];
    (*currentBet).evaluate(rankings[0], rankings[1]);
  }
}

void Game::endTurn(){
  if((*board).getNDiceRemaining() == 0){
    //  TODO: clear tiles
    evaluateLegBets(); // evaluate bets
    resetLegBets(); // put bets back
    madeLegBets.clear(); // clear list of leg bets made
    (*board).resetDice(); // put the dice back
  }

  Camel* firstPlace = (*board).getCamel(rankings[0]);
  if((*firstPlace).getSpace() > 16){
    // TODO: evaluate overall bets
    isGameOver = true;
  }

  currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

bool Game::checkIsGameOver(){
  return isGameOver;
}

void Game::takeTurnPlaceTile(int n, bool plus){
  Player* currentPlayer = players[currentPlayerIndex];
  if(plus){
    (*board).placePlusTile(n, currentPlayer);
  } else {
    (*board).placeMinusTile(n, currentPlayer);
  }
}


// Approach 4: Module docstrings
//
RCPP_EXPOSED_CLASS(Game)
  RCPP_MODULE(game_cpp) {
    using namespace Rcpp;

    class_<Game>("Game")
      .constructor<int, int, bool>()
      .constructor<const Game &>()
      .method("getPurseDF", &Game::getPurseDF)
      .method("getCamelDF", &Game::getCamelDF)
      .method("getRanking", &Game::getRanking)
      .method("takeTurnMove", &Game::takeTurnMove)
      .method("getLegBetDF", &Game::getLegBetDF)
      .method("takeTurnLegBet", &Game::takeTurnLegBet)
      .method("getNMadeLegBets", &Game::getNMadeLegBets)
      .method("evaluateLegBets", &Game::evaluateLegBets)
      .method("takeTurnPlaceTile", &Game::takeTurnPlaceTile)
      .method("checkIsGameOver", &Game::checkIsGameOver)
    ;
  }
