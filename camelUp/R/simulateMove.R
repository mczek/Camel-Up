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
  positionDFList <- list()
  # for(i in 1:N){
  #   newGame <- Game$new(g)
  #   newGame$simulateMoveOnce()
  #   # simulateMoveOnce(newGame)
  #
  #   currentDT <- data.table::as.data.table(newGame$getCamelDF())
  #   currentDT$id <- i
  #   positionDFList <- append(positionDFList, list(currentDT))
  #
  # }
  positionDFList <- parallel::mclapply(1:N, FUN = function(x){
    newGame <- Game$new(g)
    newGame$simulateMoveOnce()
    return(data.table::as.data.table(newGame$getCamelDF()))
  },
  mc.cores = getOption("mc.cores", parallel::detectCores()))
  return(data.table::rbindlist(positionDFList))

}
