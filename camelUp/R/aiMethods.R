#' Maximize Purse Increase
#'
#' Make a decision based on the current game board that maximizes the increase in the current
#' player's purse based on given historical data.
#'
#' @param gameData
#'
#' @return
#' @export
#'
#' @examples
maxPurseIncrease <- function(relevantData){
  relevantData$purseChange <- relevantData$endGamePurse - relevantData$currentPurse
  avgDecisions <- tapply(relevantData$purseChange, relevantData$Decision, mean)
  return(names(avgDecisions)[[1]])
}



agent = R6Class("agent",
                public = list(
                  observedData = NULL,
                  decisionFUN = NULL,
                  type = NULL,
                  legData = NULL,
                  fullGameData = NULL,
                  nGames = NULL,
                  initialize = function(type, FUN = NULL, observedData = NULL){
                    self$type <- type
                    self$decisionFUN <- FUN
                    self$observedData <- observedData
                    self$legData <- data.table()
                    self$fullGameData <- data.table()
                    self$nGames <- 0
                  },
                  makeDecision = function(currentState){
                    if(is.null(self$observedData)){
                      return("move")
                    }
                    relevantDataObs <- self$observedData[,-c("gameID", "isWinner")]
                    relevantData <- semi_join(relevantDataObs, currentState)
                    if(nrow(relevantData) == 0){
                      return("move")
                    }
                    return(self$decisionFUN(relevantData))
                  },
                  endLeg = function(currentPurse){
                    if(nrow(self$legData) > 0){ #make sure there is leg data
                      #print("endLeg")
                      self$legData$endLegPurse <- currentPurse
                      #print("legData")
                      #print(self$legData)
                      #print(self$fullGameData)

                      self$fullGameData <- rbind(self$fullGameData, self$legData)

                      self$legData <- data.table()
                    }

                  },
                  endGame = function(currentPurse, isWinner){
                    #print("endGame")
                    self$endLeg(currentPurse)

                    self$fullGameData$endGamePurse <- currentPurse
                    self$fullGameData$isWinner  <- isWinner
                    self$fullGameData$gameID  <- self$nGames

                    # print("fullGameData")
                    # print(self$fullGameData)
                    # print("observedData")
                    # print(self$observedData)

                    self$observedData <- rbind(self$observedData, self$fullGameData)

                    self$fullGameData <- data.table()
                    self$nGames <- self$nGames +1
                  },
                  appendLegData = function(currentData){
                    self$legData <- rbind(self$legData, currentData)
                  },
                  appendGameData = function(currentData){
                    self$observedData <- rbind(self$observedData, currentData)
                  }))

