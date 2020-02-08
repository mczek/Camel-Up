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
    newGame$takeTurnMove()
  }
  return(newGame$getCamelDF())
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
  for(i in 1:N){
    newGame <- Game$new(g)
    simulateMoveOnce(newGame)
  }

}
