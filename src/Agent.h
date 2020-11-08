#ifndef AGENT_H
#define AGENT_H

#include <Rcpp.h>
#include "Game.h"
#include <memory>



using namespace std;

class Agent {
public:
  std::string name_;
  Game* currentGame_;

  Agent(std::string name);
  std::string getName();
  void joinGame(Game* g);
  Game getGame();
};

RCPP_EXPOSED_CLASS(Agent)
#endif
