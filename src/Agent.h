#ifndef AGENT_H
#define AGENT_H

#include <Rcpp.h>
#include "Game.h"
#include <memory>



using namespace std;

class Agent {
public:
  std::string name_;
  Rcpp::DataFrame pastKnowledge_;
  shared_ptr<Game> currentGame_;

  Agent(std::string name);

  std::string getName();

  void updateKnowledge(Rcpp::DataFrame data);

  Rcpp::DataFrame getKnowledge();

  void joinGame(Game* g);

  std::string randomChoice();
};

RCPP_EXPOSED_CLASS(Agent)
#endif
