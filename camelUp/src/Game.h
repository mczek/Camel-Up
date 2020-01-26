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
  // std::vector<LegBet*> legBets;
  std::vector<std::string> colors;
  std::vector<std::string> rankings;
  // int nSpaces;
public:
  Game(int nSpaces, int nPlayers, bool d);

  DataFrame getPurseDF();

  DataFrame getCamelDF();

  std::vector<std::string> getRanking();
};

#endif
