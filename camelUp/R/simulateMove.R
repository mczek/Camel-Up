#' Simulate moving
#'
#' @param g
#'
#' @return
#' @export
#'
#' @examples
simulateMoveOnce <- function(g){
  newGame <- Game$new(g)
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
    simulateMoveOnce(g)
  }

}
