#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <Rcpp.h>
#include "Game.h"


using namespace Rcpp;


class Simulator {
private:
  Game gameObject;
public:
  Simulator(const Game & g);

  List simulateMoveEndGame(int nSims);
};



#endif

