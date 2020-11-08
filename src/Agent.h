#ifndef AGENT_H
#define AGENT_H

#include <Rcpp.h>


using namespace std;

class Agent {
public:
  std::string name_;
  Agent(std::string name);
  std::string getName();
};

RCPP_EXPOSED_CLASS(Agent)
#endif
