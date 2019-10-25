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
                  initialize = function(FUN, observedData = NULL){
                    self$decisionFUN <- FUN
                    self$observedData <- observedData
                  },
                  makeDecision = function(currentState){
                    relevantData <- semi_join(self$observedData, currentState)
                    if(nrow(relevantData) == 0){
                      return("move")
                    }
                    return(self$decisionFUN(relevantData))
                  },
                  appendData = function(currentData){
                    self$obervedData <- rbind(self$observedData, currentData)
                  }))

