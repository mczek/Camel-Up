test_that("simulateMoveOnce", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  simulateMoveOnce(g)
  # simulateMoveOnce(g)
  expect_equal(TRUE, TRUE)
})

test_that("simulateMoveOnce c++ version", {
  g <- Game$new(19, 3, FALSE)
  h <- Game$new(g)
  h$simulateMoveOnce()

  expect_equal(TRUE, TRUE)
})

test_that("mclapply?", {
  g <- Game$new(19, 3, FALSE)
  for(i in 1:100){
    #print(i)
    h <- Game$new(g)
    h$simulateMoveOnce()
  }
  expect_equal(TRUE, TRUE)
})

test_that("simulateMoveNTimes",{
  g <- Game$new(19, 3, FALSE)
  print("timing simulateMoveNTimes:")
  t <- system.time({
    simulateMoveNTimes(g, 900)
  })
  print(t)
  # simulateMoveNTimes(g, 3)
  expect_equal(TRUE, TRUE)
})
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
