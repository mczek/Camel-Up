#' Simulate moving
#'
#' @param g
#'
#' @return
#' @export
#'
#' @examples
simulateMoveOnce <- function(g){
  while(!g$checkIsGameOver()){
    g$takeTurnMove()
  }
  return(g$getCamelDF())
}


