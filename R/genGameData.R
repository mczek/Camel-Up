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
  snapshots <- list()
  while(!g$checkIsGameOver()){
    snapshot <- recordGameState(g)

    if (isP1Turn){
      player <- p1$getName()
      move <- p1$getRandomChoice()
      p1$takeTurn(move)
    } else {
      player <- p2$getName()
      move <- p2$getRandomChoice()
      p2$takeTurn(move)
    }

    snapshot$choice <- move
    snapshot$turnID <- turnID
    snapshots[[turnID]] <- snapshot

    isP1Turn <- !isP1Turn
    turnID <- turnID + 1
  }
  fullGameData <- data.table::rbindlist(snapshots)
  fullGameData$gameID <- gameID
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
#' x <- genRandomDataNTimes(10)
genRandomDataNTimes <- function(n){
  gameList <- list()
  for (i in 1:n){
    print(i)
    result <- genRandomData(i)
    gameList[[i]] <- result
  }
  return(data.table::rbindlist(gameList))
}



