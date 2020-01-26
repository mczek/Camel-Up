#include <Rcpp.h>
#include <string>
#include "Player.h"

// Define die class


class LegBet {
private:
  int value;
  std::string camelColor;
  Player* person;
public:
  Player(std::string color, int value);

  makeBet(Player* p);
};

