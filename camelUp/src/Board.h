#include <Rcpp.h>
#include <list>
#include "Space.h"

class Board {
private:
  int nSpaces;
  std::list<Space> spaces;
public:
  Board(int n);
};
