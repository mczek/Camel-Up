#include <Rcpp.h>
#include "Agent.h"
#include "LegBet.h"
#include "Game.h"
#include "Board.h"
#include "Simulator.h"
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

void Agent::joinGame(Game* g){
  currentGame_ = g;
}

Game Agent::getGame(){
  return *currentGame_;
}

std::string Agent::getRandomChoice(){
  std::vector<std::string> choices = currentGame_->getTurnOptions();
  std::random_shuffle(choices.begin(), choices.end(), randWrapper);// need to shuffle dice
  return choices[0];
}

void Agent::takeTurn(std::string decision){
  if(decision.compare("move") == 0){
    currentGame_->takeTurnMove();
  }

  if(decision.compare("legBetGreen") == 0){
    currentGame_->takeTurnLegBet("Green");
  }

  if(decision.compare("legBetWhite") == 0){
    currentGame_->takeTurnLegBet("White");
  }

  if(decision.compare("legBetYellow") == 0){
    currentGame_->takeTurnLegBet("Yellow");
  }

  if(decision.compare("legBetOrange") == 0){
    currentGame_->takeTurnLegBet("Orange");
  }

  if(decision.compare("legBetBlue") == 0){
    currentGame_->takeTurnLegBet("Blue");
  }



  // overall winner
  if(decision.compare("overallWinnerGreen") == 0){
    currentGame_->takeTurnPlaceOverallWinner("Green");
  }

  if(decision.compare("overallWinnerWhite") == 0){
    currentGame_->takeTurnPlaceOverallWinner("White");
  }

  if(decision.compare("overallWinnerYellow") == 0){
    currentGame_->takeTurnPlaceOverallWinner("Yellow");
  }

  if(decision.compare("overallWinnerOrange") == 0){
    currentGame_->takeTurnPlaceOverallWinner("Orange");
  }

  if(decision.compare("overallWinnerBlue") == 0){
    currentGame_->takeTurnPlaceOverallWinner("Blue");
  }



  // overall last place
  // overall winner
  if(decision.compare("overallLastGreen") == 0){
    currentGame_->takeTurnPlaceOverallLoser("Green");
  }

  if(decision.compare("overallLastWhite") == 0){
    currentGame_->takeTurnPlaceOverallLoser("White");
  }

  if(decision.compare("overallLastYellow") == 0){
    currentGame_->takeTurnPlaceOverallLoser("Yellow");
  }

  if(decision.compare("overallLastOrange") == 0){
    currentGame_->takeTurnPlaceOverallLoser("Orange");
  }

  if(decision.compare("overallLastBlue") == 0){
    currentGame_->takeTurnPlaceOverallLoser("Blue");
  }
}

List Agent::simulateLeg(){
  // Rcout << "simlauteLeg called\n";
  int kNSIMS = 100;
  Simulator sim(currentGame_->getBoard());
  // // Rcout << "getBoard completed\n";
  // Rcout << currentGame_->getBoard().getNDiceRemaining() << "\n";
  // Rcout << currentGame_->getBoard().getFirstPlaceSpace() << "\n";
  // Rcout << currentGame_->getBoard().getRanking()[0] << "\n";

  Rcpp::List results = sim.simulateDecision(TRUE, kNSIMS);
  // Rcout << "simulation complete\n";
  return results["ranking"];
}

std::string Agent::getLegBetMaxEV(){
  // Rcout << "\neval leg bets for max EV\n";
  List ranking = simulateLeg();
  // Rcout << "\nranking calculated\n";
  std::map<std::string, std::map<int, int>> distribution;
  std::vector<std::string> colors = {"Green", "White", "Yellow", "Orange", "Blue"};
  for(int i=0; i<colors.size(); i++){
    for(int j=0; j<colors.size(); j++){
      distribution[colors[i]][j] = 0;
    }
  }
  // Rcout << "\ndistribution initialized\n";
  Rcpp::StringVector simData = simulateLeg()[0];

  int nElts = simData.size();
  int nSims = nElts/5;

  for(int i=0; i<nElts;i++){
    std::string current(simData[i]);
    distribution[current][i % 5]++;
  }
  // Rcout << "\ndistribution filled\n";

  std::map<std::string, float> expVals;
  float maxValue = -2;
  std::string maxColor = colors[0];

  // Rcout << "\ncheck legBets\n";
  for(int i=0; i<colors.size();i++){
    std::string currentColor = colors[i];
    std::map<int, int> colorDistribution = distribution[currentColor];

    std::stack<std::shared_ptr<LegBet>> betStack = currentGame_->legBets[currentColor];
    int nBetsLeft = betStack.size();
    if (nBetsLeft > 0){
      int firstCoins = betStack.top()->getValue();
      float value = firstCoins*colorDistribution[0] + 2*colorDistribution[1] -colorDistribution[2] - colorDistribution[3] - colorDistribution[4];
      value = value / nSims;
      expVals[currentColor] = value;

      if (value > maxValue){
        maxColor = currentColor;
        maxValue = value;
      }
      // Rcout << currentColor << "\t" << expVals[currentColor] << "\t" << firstCoins << "\t" << expVals[currentColor] << "\n";
    }
  }

  if (maxValue == -2) {
    return "move";
  }

  // Rcout << simData[0] << "first element?";
  return maxColor;
}



RCPP_MODULE(agent_cpp){
  using namespace Rcpp;
  class_<Agent>("Agent")
  .constructor<std::string>()
  .method("getName", &Agent::getName)
  .method("joinGame", &Agent::joinGame)
  .method("getGame", &Agent::getGame)
  .method("getRandomChoice", &Agent::getRandomChoice)
  .method("takeTurn", &Agent::takeTurn)
  .method("simulateLeg", &Agent::simulateLeg)
  .method("getLegBetMaxEV", &Agent::getLegBetMaxEV)
  ;
}
