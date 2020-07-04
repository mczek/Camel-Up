#ifndef SPACE_H
#define SPACE_H

#include <Rcpp.h>
#include <stack>
#include "Camel.h"
#include "Player.h"
#include <memory>

using namespace Rcpp;


class Space {
private:
  int position;
  std::stack <std::shared_ptr<Camel>> camels;
  int nCamels;
  bool plusTile, minusTile;
  Player* tilePlacedBy;
  std::vector<std::string> camelStrings; // used to make copies
public:
  Space();

  Space(int pos);

  Space(Space & s);

  // ~Space();

  int getPosition();

  void addCamel(std::shared_ptr<Camel> c);

  std::shared_ptr<Camel> removeCamel();

  int getNCamels();

  bool getPlusTile();

  bool getMinusTile();

  // for both of these functions the camel stacks are assumed to be reversed
  void addCamelsTop(std::stack<std::shared_ptr<Camel>> camelsToMove); // used for when camels move to a space from behind
  void addCamelsBottom(std::stack<std::shared_ptr<Camel>> camelsToMove); // used for when camels move to a space from behind

  int testAddCamel();

  void setPlusTile(Player* p);

  void setMinusTile(Player* p);

  Player* getTilePlacedBy();

  void setTilePlacedBy(Player*p);

  std::vector<std::shared_ptr<Camel>>  getCamelPointers(); // TODO: needs to be tested

  std::vector<std::string> getCamelStrings(); // TODO: needs to be tested

  void clearSpace();
};
#endif
