#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <Rcpp.h>
#include "Board.h"


using namespace Rcpp;


class Simulator {
private:
  Board boardObject;
public:

  Simulator(const Board & g);

  List simulateMoveEndGame(int nSims);
};



#endif

