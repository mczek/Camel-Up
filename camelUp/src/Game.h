#ifndef GAME_H
#define GAME_H

#include <Rcpp.h>
#include <stack>
#include "Player.h"
#include "Board.h"
#include "LegBet.h"

using namespace Rcpp;


class Game {
private:
  std::vector<Player*> players;
  Board* board;
  std::map<std::string, std::stack<LegBet*>> legBets; // each color has a stack, all contained in a map
  std::vector<std::string> colors;
  std::vector<std::string> rankings;
  int currentPlayerIndex;
  std::vector<LegBet*> madeLegBets;
  bool isGameOver;
  int nSpaces;
  bool debug;
public:
  Game(int nSpaces, int nPlayers, bool d);

  Game(const Game & g);

  DataFrame getPurseDF();

  DataFrame getCamelDF();

  std::vector<std::string> getRanking();

  std::string takeTurnMove();

  void resetLegBets();

  DataFrame getLegBetDF();

  void takeTurnLegBet(std::string camelColor);

  int getNMadeLegBets();

  void evaluateLegBets();

  void endTurn();

  bool checkIsGameOver();

  void takeTurnPlaceTile(int n, bool plus);

  int getFirstPlaceSpace();

};

#endif
