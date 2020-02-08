test_that("simulateMoveOnce", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  simulateMoveOnce(g)
  # simulateMoveOnce(g)
  expect_equal(TRUE, TRUE)
})

# test_that("simulateMoveNTimes",{
#   set.seed(1)
#   g <- Game$new(19, 3, TRUE)
#   # for(i in 1:3){
#   #   newGame <- Game$new(g)
#   # }
#   simulateMoveNTimes(g, 3)
#   expect_equal(TRUE, TRUE)
# })

test_that("simulateMoveOnce c++ version", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  h <- g$simulateMoveOnce()
  expect_equal(TRUE, TRUE)
})
