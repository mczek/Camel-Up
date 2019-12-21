#' @useDynLib CamelUp
NULL

# Rcpp::loadModule("double_cpp", TRUE)
Rcpp::loadModule("die_cpp", TRUE)
Rcpp::loadModule("camel_cpp", TRUE)
Rcpp::loadModule("space_cpp", TRUE)
Rcpp::loadModule("board_cpp", TRUE)
