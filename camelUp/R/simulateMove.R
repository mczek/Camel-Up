#' Simulate moving
#'
#' @param g
#'
#' @return
#' @export
#'
#' @examples
simulateMoveOnce <- function(g){
  newGame <- g #TODO: come back here to fix
  while(!newGame$checkIsGameOver()){
    # print(newGame$getCamelDF())
    newGame$takeTurnMove()
  }
  print("endSimOnce")
  return(newGame)
}

#' Simulate moving N times
#'
#' @param g
#' @param N
#'
#' @return
#' @export
#'
#' @examples
simulateMoveNTimes <- function(g, N){
  # works:
  gameVec <- NULL
  for(i in 1:N){
    newGame <- Game$new(g)
    gameVec[i] <- simulateMoveOnce(newGame)
  }

}
