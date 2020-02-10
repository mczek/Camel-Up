test_that("simulateMoveOnce", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  simulateMoveOnce(g)
  # simulateMoveOnce(g)
  expect_equal(TRUE, TRUE)
})

# test_that("simulateMoveNTimes",{
#
#
#   for(i in 1:100){
#     print(i)
#     g <- Game$new(19, 3, FALSE)
#     g$simulateMoveOnce()
#   #   newGame <- Game$new(g)
#   }
#   # simulateMoveNTimes(g, 3)
#   expect_equal(TRUE, TRUE)
# })
#
# test_that("simulateMoveOnce c++ version", {
#   # set.seed(1)
#   g <- Game$new(19, 3, FALSE)
#   for(i in 1:100){
#     print(i)
#     simulateMoveOnce(g)
#   }
#   expect_equal(TRUE, TRUE)
# })
