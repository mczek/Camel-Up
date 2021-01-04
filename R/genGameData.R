#' @export
recordGameState <- function(game){
  camelPositions <- game$getCamelDF()
  camelPositions <- tidyr::pivot_wider(camelPositions,
                                       id_cols = Color,
                                       names_from = Color,
                                       values_from = c(Space, Height))
  purseDF  <- game$getPurseDF()
  purseDF <- tidyr::spread(purseDF, Player, Coins)

  return(cbind(purseDF, camelPositions))

}

#' @export
getRandomChoiceAgent <-  function(agent){
  return(agent$getRandomChoice())
}

#' @export
getLegBetMaxEVAgent <- function(agent) {
  color <- agent$getLegBetMaxEV(FALSE)
  return(color)
}

#' @export
getLegBetMoveMaxEVAgent <- function(agent) {
  color <- agent$getLegBetMaxEV(TRUE)
  return(color)
}

#' @export
getLegBetFirstCamelAgent <- function(agent) {
  color <- agent$getLegBetFirstCamel()
  return(color)
}

#' @export
getMoveMaxLegWinAgent <- function(agent) {
  color <- agent$getMaxWinLegProbDecision()
  return(color)
}

#' @export
getMaxWinProbEV50 <- function(agent) {
  color <- agent$maxWinProbEV50()
  return(color)
}

#' @export
getMaxWinProbEV75Lead <- function(agent) {
  color <- agent$maxWinProbEV75Lead()
  return(color)
}

#' @export
getMaxWinProbEVFurthestCamel <- function(agent) {
  color <- agent$maxWinProbEVFurthestCamel()
  return(color)
}



#' Title
#'
#' @return
#' @importFrom data.table rbindlist
#' @importFrom tidyr spread
#' @export
genData <- function(gameID, agent1Name, agent1FUN, agent2Name, agent2FUN){
  # print("new game ...")
  p1 <- Agent$new(agent1Name)
  p2 <- Agent$new(agent2Name)
  g <- Game$new(19, 2, FALSE)

  p1$joinGame(g)
  p2$joinGame(g)

  isP1Turn <- TRUE
  turnID <- 1
  snapshots <- list()
  while(!g$checkIsGameOver()){
    snapshot <- recordGameState(g)

    if (isP1Turn){
      playerName <- p1$getName()
      move <- agent1FUN(p1)
    } else {
      playerName <- p2$getName()
      move <- agent2FUN(p2)
    }
    # print(paste("turnID, move", turnID, move))
    if(move == "move") {
      g$takeTurnMove()
    } else {
      g$takeTurnLegBet(move)
    }


    snapshot$name <- playerName
    snapshot$choice <- move
    snapshot$turnID <- turnID
    snapshots[[turnID]] <- snapshot

    isP1Turn <- !isP1Turn
    turnID <- turnID + 1
  }
  fullGameData <- data.table::rbindlist(snapshots)
  fullGameData$gameID <- gameID
  fullGameData$p0Strat <- agent1Name
  fullGameData$p1Strat <- agent2Name
  return(fullGameData)
}


#' Title
#'
#' @param n number of games to play
#'
#' @importFrom data.table rbindlist
#' @importFrom dplyr left_join
#'
#' @return
#' @export
#'
#' @examples
#' x <- genRandomDataNTimes(10, "random", getRandomChoiceAgent, "random", getRandomChoiceAgent)
genDataNTimes <- function(n, agent1Name, agent1FUN, agent2Name, agent2FUN){
  gameList <- list()
  for (i in 1:n){
    print(i)
    result <- genData(i, agent1Name, agent1FUN, agent2Name, agent2FUN)
    gameList[[i]] <- result
  }
  return(data.table::rbindlist(gameList))
}


#' Title
#'
#' @param n number of games to play
#'
#' @importFrom data.table rbindlist
#' @importFrom dplyr left_join
#'
#' @return
#' @export
#'
#' @examples
#' x <- genRandomDataNTimes(10, "random", getRandomChoiceAgent, "random", getRandomChoiceAgent)
genRandomDataNTimes <- function(n){
  gameList <- list()
  for (i in 1:n){
    print(i)
    result <- genData(i, "random", getRandomChoiceAgent, "random", getRandomChoiceAgent)
    gameList[[i]] <- result
  }
  return(data.table::rbindlist(gameList))
}


#' Title
#'
#' @param n number of games to play
#'
#' @importFrom data.table rbindlist
#' @importFrom dplyr left_join
#'
#' @return
#' @export
#'
#' @examples
#' x <- genRandomDataNTimes(10, "random", getRandomChoiceAgent, "random", getRandomChoiceAgent)
genLegBetMaxEVDataNTimes <- function(n){
  gameList <- list()
  for (i in 1:n){
    print(i)
    result <- genData(i, "legBetMaxEV", getLegBetMaxEVAgent, "legBetMaxEV", getLegBetMaxEVAgent)
    gameList[[i]] <- result
  }
  return(data.table::rbindlist(gameList))
}

#' Title
#'
#' @param n number of games to play
#'
#' @importFrom data.table rbindlist
#' @importFrom dplyr left_join
#'
#' @return
#' @export
#'
#' @examples
#' x <- genRandomDataNTimes(10, "random", getRandomChoiceAgent, "random", getRandomChoiceAgent)
genLegBetMoveMaxEVDataNTimes <- function(n){
  gameList <- list()
  for (i in 1:n){
    print(i)
    result <- genData(i, "legBetMoveMaxEV", getLegBetMoveMaxEVAgent, "legBetMoveMaxEV", getLegBetMoveMaxEVAgent)
    gameList[[i]] <- result
  }
  return(data.table::rbindlist(gameList))
}

#' Title
#'
#' @param n number of games to play
#'
#' @importFrom data.table rbindlist
#' @importFrom dplyr left_join
#'
#' @return
#' @export
#'
#' @examples
#' x <- genRandomDataNTimes(10, "random", getRandomChoiceAgent, "random", getRandomChoiceAgent)
genLegBetFirstCamelDataNTimes <- function(n){
  gameList <- list()
  for (i in 1:n){
    print(i)
    result <- genData(i, "legBetFirstCamel", getLegBetFirstCamel, "legBetFirstCamel", getLegBetFirstCamel)
    gameList[[i]] <- result
  }
  return(data.table::rbindlist(gameList))
}






