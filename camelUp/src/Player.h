#ifndef PLAYER_H
#define PLAYER_H

#include <Rcpp.h>
#include <string>

// Define die class


class Player {
private:
  std::string name;
  int coins;
public:
  Player(std::string n);

  Player(const Player & p);

  void addCoins(int n);

  std::string getName();

  int getCoins();
};

#endif
