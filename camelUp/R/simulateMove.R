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
  return(g$getCamelDF())
}

#
# g <- Game$new(19, 3, TRUE)
# simulateMoveOnce(g)
