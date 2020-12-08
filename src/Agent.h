#ifndef AGENT_H
#define AGENT_H

#include <Rcpp.h>
#include "Player.h"
#include "Game.h"
#include "Simulator.h"
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

  std::string getRandomChoice();

  void takeTurn(std::string decision);

  List simulateLeg();

  std::string getLegBetMaxEV(bool canMove);

  std::string getLegBetFirstCamel();

  std::string getMaxWinLegProbDecision();
};

RCPP_EXPOSED_CLASS(Agent)
#endif
