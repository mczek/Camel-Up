#include <Rcpp.h>
#include "Agent.h"
#include "Player.h"
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

std::string Agent::getLegBetMaxEV(bool canMove){
  // Rcout << "\neval leg bets for max EV\n";
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
  std::string maxColor = "move";
  if (canMove) {
    maxValue = 1;
  }


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

  // Rcout << simData[0] << "first element?";
  return maxColor;
}

std::string Agent::getLegBetFirstCamel(){

  std::map<std::string, std::stack<std::shared_ptr<LegBet> > > betMap = currentGame_->legBets;
  std::vector<std::string> ranking = currentGame_->getRanking();

  std::string firstColor = ranking[0];
  if (betMap[firstColor].size() > 0) {
    return firstColor;
  }
  // for (int i=0; i<5; i++){
  //   std::string currentColor = ranking[i];
  //   if (betMap[currentColor].size() > 0) {
  //     return currentColor;
  //   }
  // }
  return "move";

}



std::string Agent::getMaxWinLegProbDecision(){
  std::vector<std::shared_ptr<LegBet>> currentlyMadeBets = currentGame_->madeLegBets;


  int playerIndex = currentGame_->currentPlayerIndex;
  std::string currentPlayerName = currentGame_->players[playerIndex]->name;
  // Rcout << "\n" << currentPlayerName << "\n";


  int opponentCoins = 0;
  int myselfCoins = 0;
  for(int i=0; i<currentGame_->players.size(); i++){
    std::shared_ptr<Player> p = currentGame_->players[i];
    if (p->name.compare(currentPlayerName)) {
      myselfCoins += p->getCoins();
    } else {
      opponentCoins += p->getCoins();
    }
  }
  int lead = myselfCoins - opponentCoins;



  std::shared_ptr<Player> myself = std::make_shared<Player>("myself");
  std::shared_ptr<Player> opponent = std::make_shared<Player>("opponent");

  // add current bets to duplicateBets
  std::vector<std::shared_ptr<LegBet>> duplicateBets;
  for (int i=0; i<currentlyMadeBets.size(); i++) {
    std::shared_ptr<LegBet> currentBet = currentlyMadeBets[i];
    std::shared_ptr<Player> bettor = currentBet->person;
    std::string bettorName = bettor->getName();

    std::shared_ptr<LegBet> newBet = std::make_shared<LegBet>(currentBet->camelColor, currentBet->getValue());
    if(bettorName.compare(currentPlayerName) == 0) {
      newBet->makeBet(myself);
    } else {
      newBet->makeBet(opponent);
    }

    duplicateBets.push_back(newBet);

    // Rcout << currentBet->getValue() << "\n";
    // Rcout << currentBet->person->name << "\n";
    // Rcout << currentBet->camelColor << "\n";
    // Rcout << duplicateBets.size() << "\n";
  }


  // get possible bets
  std::map<std::string, LegBet> availableBets;
  std::vector<std::string> availableColors;
  for (int i=0; i<currentGame_->colors.size();i++){
    std::string currentColor = currentGame_->colors[i];
    std::stack<std::shared_ptr<LegBet>> currentStack = currentGame_->legBets[currentColor];
    if(currentStack.size()>0){
      availableColors.push_back(currentColor);
      LegBet nextBet = LegBet(currentColor, currentStack.top()->getValue());
      nextBet.makeBet(myself);
      availableBets[currentColor] = nextBet;
    }
  }


  // simulate and make a decision
  Rcpp::StringVector simData = simulateLeg()[0];
  // Rcout << "length of simData = " << simData.size() << "\n";
  int nElts = simData.size();
  int nSims = nElts/5;

  int oldLead = lead;
  std::map<std::string, std::vector<int>> colorLeadMap;
  for(int simID=0; simID<nSims; simID++){
    int begin = simID*5;
    std::vector<std::string> endLegRanking;
    for(int i=0; i<5;i++){
      std::string c = Rcpp::as<std::string>(simData(begin+i));
      endLegRanking.push_back(c);
    }

    int lead = oldLead;
    // evaluate existing bets
    for(int i=0; i<duplicateBets.size(); i++){
      duplicateBets[i]->evaluate(endLegRanking[0], endLegRanking[1]);
    }

    lead += myself->getCoins() - opponent->getCoins();
    // Rcout << "lead" << lead << "\n";

    if (lead > -1) {
      colorLeadMap["move"].push_back(1); // win
    } else {
      colorLeadMap["move"].push_back(0);
    }
    // for each possible bet, evaluate it for each sim result

    for(int i=0; i<availableColors.size(); i++) {
      std::string c = availableColors[i];
      LegBet possibleBet = availableBets[c];
      int finalLead = lead + possibleBet.evaluate(endLegRanking[0], endLegRanking[1]);
      // Rcout << "finalLead: \t" << c << "\t" << finalLead << "\n";

      if (finalLead > 0){
        colorLeadMap[c].push_back(1); // win
      } else {
        colorLeadMap[c].push_back(0);
      }
    }

    myself->addCoins(-myself->getCoins());
    opponent->addCoins(-opponent->getCoins());

    // Rcout <<"should be 0 coins\t" << myself->getCoins() << "\t" << opponent->getCoins() << "\n";

  }

  std::string decision = "move";
  float maxWinProb = std::accumulate(colorLeadMap["move"].begin(), colorLeadMap["move"].end(), 0.0) / nSims;
  // Rcout << "move win prob = \t" << maxWinProb << "\n";
  for(int i=0; i<availableColors.size(); i++) {
    std::string c = availableColors[i];
    float winProb = std::accumulate(colorLeadMap[c].begin(), colorLeadMap[c].end(), 0.0) / nSims;
    // Rcout << "\n" << c << "\t" << winProb << "\t" << decision << "\t" << maxWinProb << "\n";
    if (winProb > maxWinProb) {
      maxWinProb = winProb;
      decision = c;
    }
  }

  return decision;
}


std::string Agent::maxWinProbEV50() {
  int kNSIMS = 1000;
  Simulator sim(currentGame_->getBoard());
  // // Rcout << "getBoard completed\n";
  // Rcout << currentGame_->getBoard().getNDiceRemaining() << "\n";
  // Rcout << currentGame_->getBoard().getFirstPlaceSpace() << "\n";
  // Rcout << currentGame_->getBoard().getRanking()[0] << "\n";
  Rcpp::List results = sim.simulateDecision(TRUE, kNSIMS);
  // Rcout << "sim run\n";
  // Rcpp::DataFrame positionData = results["position"];
  // Rcout << "positionDF extracted\n";
  Rcpp::List positionData = results["position"];
  Rcpp::IntegerVector spaceVec = positionData[1];
  // Rcout << "spaceVec extracted\n";
  int count = 0;
  for(int i=0; i<kNSIMS; i++) {
    Rcpp::IntegerVector singleResult = spaceVec[Rcpp::Range(5*i, 5*i + 4)];
    int furthestSpace = Rcpp::max(singleResult);
    // Rcout << "maxSpace" << furthestSpace << "\n";
    if (furthestSpace > 16) { // game ended
      count ++;
    }
  }
  // Rcout << "count = " << count << "\n";
  if (count >  kNSIMS/2) {
    // Rcout << currentGame_->getFirstPlaceSpace() << "\n";
    return getMaxWinLegProbDecision();
  }
  return getLegBetMaxEV(true);
}


std::string Agent::maxWinProbEV75Lead() {
  int playerIndex = currentGame_->currentPlayerIndex;
  std::string currentPlayerName = currentGame_->players[playerIndex]->name;

  int opponentCoins = 0;
  int myselfCoins = 0;
  for(int i=0; i<currentGame_->players.size(); i++){
    std::shared_ptr<Player> p = currentGame_->players[i];
    if (p->name.compare(currentPlayerName)) {
      myselfCoins += p->getCoins();
    } else {
      opponentCoins += p->getCoins();
    }
  }
  int lead = myselfCoins - opponentCoins;




  int kNSIMS = 1000;
  Simulator sim(currentGame_->getBoard());
  // // Rcout << "getBoard completed\n";
  // Rcout << currentGame_->getBoard().getNDiceRemaining() << "\n";
  // Rcout << currentGame_->getBoard().getFirstPlaceSpace() << "\n";
  // Rcout << currentGame_->getBoard().getRanking()[0] << "\n";
  Rcpp::List results = sim.simulateDecision(TRUE, kNSIMS);
  Rcout << "sim run\n";
  // Rcpp::DataFrame positionData = results["position"];
  // Rcout << "positionDF extracted\n";
  Rcpp::List positionData = results["position"];
  Rcpp::IntegerVector spaceVec = positionData[1];
  // Rcout << "spaceVec extracted\n";
  int count = 0;
  for(int i=0; i<kNSIMS; i++) {
    Rcpp::IntegerVector singleResult = spaceVec[Rcpp::Range(5*i, 5*i + 4)];
    int furthestSpace = Rcpp::max(singleResult);
    // Rcout << "maxSpace" << furthestSpace << "\n";
    if (furthestSpace > 16) { // game ended
      count ++;
    }
  }
  // Rcout << "count = " << count << "\n";
  // (count >  kNSIMS*6/20)
  if ((count > kNSIMS/4)){
    return getMaxWinLegProbDecision();
  }
  return getLegBetMaxEV(true);
}


std::string Agent::maxWinProbEVFurthestCamel() {
  if (currentGame_->getFirstPlaceSpace() > 12){
    return getMaxWinLegProbDecision();
  }
  return getLegBetMaxEV(true);
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
  .method("getLegBetFirstCamel", &Agent::getLegBetFirstCamel)
  .method("getMaxWinLegProbDecision", &Agent::getMaxWinLegProbDecision)
  .method("maxWinProbEV50", &Agent::maxWinProbEV50)
  .method("maxWinProbEV75Lead", &Agent::maxWinProbEV75Lead)
  .method("maxWinProbEVFurthestCamel", &Agent::maxWinProbEVFurthestCamel)
  ;
}
