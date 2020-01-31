#ifndef SPACE_H
#define SPACE_H

#include <Rcpp.h>
#include <stack>
#include "Camel.h"
#include "Player.h"

using namespace Rcpp;


class Space {
private:
  int position;
  std::stack <Camel*> camels;
  int nCamels;
  bool plusTile, minusTile;
  Player* tilePlacedBy;
public:
  Space();

  Space(int pos);

  Space(const Space & s);

  int getPosition();

  void addCamel(Camel * c);

  Camel * removeCamel();

  int getNCamels();

  bool getPlusTile();

  bool getMinusTile();

  // for both of these functions the camel stacks are assumed to be reversed
  void addCamelsTop(std::stack<Camel*> camelsToMove); // used for when camels move to a space from behind
  void addCamelsBottom(std::stack<Camel*> camelsToMove); // used for when camels move to a space from behind

  int testAddCamel();

  void setPlusTile(Player* p);

  void setMinusTile(Player* p);

  Player* getTilePlacedBy();

  void setTilePlacedBy(Player*p);

};
#endif
