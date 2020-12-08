#ifndef PLAYER_H
#define PLAYER_H

#include <Rcpp.h>
#include <string>

// Define die class


class Player {
private:
  int coins;

  std::string overallFirstPlaceColor;
  std::string overallLastPlaceColor;
public:
  std::string name;

  Player();

  Player(std::string n);

  Player(const Player & p);

  void addCoins(int n);

  std::string getName();

  int getCoins();

  void setOverallFirst(std::string color);

  void setOverallLast(std::string color);

  std::string getOverallFirst();

  std::string getOverallLast();
};
RCPP_EXPOSED_CLASS(Player)
#endif
