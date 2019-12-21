#include <Rcpp.h>
#include <list>
#include <vector>
#include <algorithm>
#include "Space.h"
#include "Die.h"
#include "Camel.h"

class Board {
private:
  int nSpaces;
  std::vector<Space> spaces;
  std::vector<Die> dice;
  std::vector<Camel> camels;
public:
  Board(int n);

  int getNDiceRemaining();

  void resetDice();

  void initCamels();

  int getNCamels();
};
