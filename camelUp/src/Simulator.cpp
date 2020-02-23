#include <Rcpp.h>
#include "Simulator.h"
#include "Game.h"


using namespace Rcpp;

// Define space class

//' @name Simulator
//' @title Encapsulates a double
//' @description Type the name of the class to see its methods
//' @field new Constructor
//' @field mult Multiply by another Double object \itemize{
//' \item Paramter: other - The other Double object
//' \item Returns: product of the values
//' }
//' @export


Simulator::Simulator(const Game & g){
  gameObject = Game(g);
}

List Simulator::simulateMoveEndGame(int nSims){
  Rcout << "function called";
  int nCamels = 5;
  int vecLength = nSims*nCamels;
  Game * gamePtr = &gameObject;

  Rcpp::CharacterVector *camelColors = new CharacterVector(vecLength);
  Rcpp::IntegerVector *spaceVec = new IntegerVector(vecLength);
  Rcpp::IntegerVector *heightVec = new IntegerVector(vecLength);

  Game duplicateGames[nSims];
  for(int i=0; i<nSims;i++){
    duplicateGames[i] = Game(*gamePtr);
  }

  for(int i=0; i<nSims; i++){
    Game tempGame = duplicateGames[i];
    tempGame.progressToEndGame();
    // Rcout << "test";
    Board * tempBoard = tempGame.getBoard();
    // Rcout << "test done";
    (*tempBoard).fillCamelPosArrays(camelColors, spaceVec, heightVec, i*nCamels);
  }


  DataFrame df = DataFrame::create(Named("Color") = *camelColors, Named("Space") = *spaceVec, Named("Height") = *heightVec);
  return List::create(Named("position") = df);
}


//
RCPP_EXPOSED_CLASS(Simulator)
  RCPP_MODULE(simulator_cpp) {
    using namespace Rcpp;

    class_<Simulator>("Simulator")
      .constructor<Game>()
      .method("simulateMoveEndGame", &Simulator::simulateMoveEndGame)
    ;
  }
