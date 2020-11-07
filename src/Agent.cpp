#include <Rcpp.h>
#include "Agent.h"
#include "Game.h"
using namespace Rcpp;
using namespace std;
#include <memory>

// Define agent class



//' @name Agent
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export

Agent::Agent(std::string name){
  name_ = name;
}

std::string Agent::getName(){
  return name_;
}

void Agent::updateKnowledge(Rcpp::DataFrame data){
  pastKnowledge_ = data;
}

Rcpp::DataFrame Agent::getKnowledge(){
  return pastKnowledge_;
}

void Agent::joinGame(Game* g){
  currentGame_ = shared_ptr<Game>(g);
}

std::string Agent::randomChoice(){
  std::vector<std::string> options = currentGame_->getTurnOptions();
  return options[0];
}



RCPP_MODULE(agent_cpp){
  using namespace Rcpp;
  class_<Agent>("Agent")
  .constructor<std::string>()
  .method("getName", &Agent::getName)
  .method("updateKnowledge", &Agent::updateKnowledge)
  .method("getKnowledge", &Agent::getKnowledge)
  .method("joinGame", &Agent::joinGame)
  .method("randomChoice", &Agent::randomChoice)
  ;
}
