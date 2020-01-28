#ifndef BOARD_H
#define BOARD_H

#include <Rcpp.h>
#include <list>
#include <vector>


#include <algorithm>
#include <string>
#include "Space.h"
#include "Die.h"
#include "Camel.h"

class Board {
private:
  int nSpaces;
  std::vector<Space*> spaces;
  std::vector<Die> dice;
  // std::vector<Camel> camels;
  std::map<std::string, Camel*> camels;
  std::vector<std::string> colors;
  bool debug;
  std::vector<std::string> ranking;
public:
  Board(int n, bool d = false);

  Board(const Board & b);

  int getNDiceRemaining();

  void resetDice();

  void initCamels();

  int getNCamels();

  Rcpp::DataFrame getCamelDF();

  std::string moveTurn();

  void generateRanking();

  std::vector<std::string> getRanking();

  Camel* getCamel(std::string color);

  void placePlusTile(int n, Player* p);

  void placeMinusTile(int n, Player* p);

  Space* getSpaceN(int n);

  std::vector<Die> getDice();

  void setDice(std::vector<Die>);
};

#endif
