#ifndef SPACE_H
#define SPACE_H

#include <Rcpp.h>
#include <stack>
#include "Camel.h"


class Space {
private:
  int position;
  std::stack <Camel> camels;
  int nCamels;
  bool plusTile, minusTile;
public:
  Space();

  Space(int pos);

  int getPosition();

  void addCamel(Camel c);

  Camel removeCamel();

  int getNCamels();

  bool getPlusTile();

  bool getMinusTile();

};

#endif
