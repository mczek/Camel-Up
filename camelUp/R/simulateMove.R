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
#' @import foreach
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
  positionDFList <- lapply(1:N, FUN = function(x){
    newGame <- Game$new(g)
    newGame$simulateMoveOnce()
    return(data.table::as.data.table(newGame$getCamelDF()))
  })
#
#   # no_cores <- parallel::detectCores()
#   # cl <- parallel::makeCluster(no_cores)
#   # doParallel::registerDoParallel()
#   # positionDFList<-foreach::foreach(i=1:N, .combine = rbind) %dopar% {
#   #     newGame <- Game$new(g)
#   #     newGame$simulateMoveOnce()
#   #     newGame$getCamelDF()
#   #   }
#   #
#   # doParallel::stopImplicitCluster()

  # cl <- parallel::makeCluster(getOption("cl.cores", 2))
  # l <- list(1:N)
  # positionDFList<- parallel::parLapply(cl, l, function(x) {
  #     newGame <- Game$new(g)
  #     newGame$simulateMoveOnce()
  #     return(data.table::as.data.table(newGame$getCamelDF()))
  # })
  return(data.table::rbindlist(positionDFList))

}
