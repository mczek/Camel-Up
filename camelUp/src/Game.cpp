#include <Rcpp.h>
#include <stack>
#include "Player.h"
#include "Board.h"
#include "LegBet.h"
#include "Game.h"

using namespace Rcpp;

// Define space class

//' @name Game
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export


Game::Game(int nSpaces, int nPlayers, bool d){
  colors = {"Green", "White", "Yellow", "Orange", "Blue"};
  board = new Board(nSpaces, d);

  for(int i=0;i<nPlayers;i++){
    players.push_back(new Player("Player " + toString(i)));
  }
}

DataFrame Game::getPurseDF(){
  std::vector<std::string> names;
  std::vector<int> purseValues;

  int nPlayers = players.size();
  for(int i=0;i<nPlayers;i++){
    Player* currentPlayer = players[i];
    names.push_back((*currentPlayer).getName());
    purseValues.push_back((*currentPlayer).getCoins());
  }

  DataFrame df = DataFrame::create(Named("Player") = names, Named("Coins") = purseValues);
  return df;
}




// Approach 4: Module docstrings
//
RCPP_EXPOSED_CLASS(Game)
  RCPP_MODULE(game_cpp) {
    using namespace Rcpp;

    class_<Game>("Game")
      .constructor<int, int, bool>()
      .method("getPurseDF", &Game::getPurseDF)
    ;
  }
