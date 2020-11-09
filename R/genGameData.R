#' Title
#'
#' @return
#' @importFrom data.table rbindlist
#' @importFrom tidyr spread
#' @export
#'
#' @examples
genRandomData <- function(gameID){
  p1 <- Agent$new("P0")
  p2 <- Agent$new("P1")
  g <- Game$new(19, 2, FALSE)

  p1$joinGame(g)
  p2$joinGame(g)

  isP1Turn <- TRUE
  turnID <- 1
  positionsList <- list()
  decisionsList <- list()
  purseList <- list()
  while(!g$checkIsGameOver()){
    camelPositions <- g$getCamelDF()
    camelPositions$turnID <- turnID
    camelPositions$gameID <- gameID
    positionsList[[turnID]] <- camelPositions

    purseDF  <- g$getPurseDF()
    purseDF <- tidyr::spread(purseDF, Player, Coins)

    purseDF$turnID <- turnID
    purseDF$gameID <- gameID
    purseList[[turnID]] <- purseDF


    if (isP1Turn){
      player <- p1$getName()
      move <- p1$getRandomChoice()
      p1$takeTurn(move)
    } else {
      player <- p2$getName()
      move <- p2$getRandomChoice()
      p2$takeTurn(move)
    }

    decisionsList[[turnID]] <- data.frame("turnID" = turnID,
                               "choice" = move,
                               "gameID" = gameID)
    rawPurseData <- g$getPurseDF()

    isP1Turn <- !isP1Turn
    turnID <- turnID + 1
  }
  positionsDF <- data.table::rbindlist(positionsList)
  choiceDF <- data.table::rbindlist(decisionsList)
  purseData <- data.table::rbindlist(purseList)
  return(list(positionsDF, choiceDF, purseData))
}


#' Title
#'
#' @param n
#'
#' @importFrom data.table rbindlist
#'
#' @return
#' @export
#'
#' @examples
#' x <- genRandomDataNTimes(10)
genRandomDataNTimes <- function(n){
  positionsList <- list()
  choiceDF <- list()
  purseDF <- list()
  for (i in 1:n){
    result <- genRandomData(i)
    positionsList[[i]] <- result[[1]]
    choiceDF[[i]] <- result[[2]]
    purseDF[[i]] <- result[[3]]
  }

  return(list(data.table::rbindlist(positionsList),
              data.table::rbindlist(choiceDF),
              data.table::rbindlist(purseDF)))
}



