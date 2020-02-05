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
#   simulateMoveNTimes(g, 3)
#   expect_equal(TRUE, TRUE)
# })

