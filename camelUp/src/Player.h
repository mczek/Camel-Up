#include <Rcpp.h>
#include <string>

// Define die class


class Player {
private:
  std::string name;
  int coins;
public:
  Player(std::string n);

  void addCoins(int n);

  std::string getName();

  int getCoins();
};

