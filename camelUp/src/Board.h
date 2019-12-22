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
  std::vector<Space> spaces;
  std::vector<Die> dice;
  // std::vector<Camel> camels;
  std::map<std::string, Camel> camels;
  std::vector<std::string> colors;
public:
  Board(int n);

  int getNDiceRemaining();

  void resetDice();

  void initCamels();

  int getNCamels();

  Rcpp::DataFrame getCamelDF();

  std::string moveTurn();
};
