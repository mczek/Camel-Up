test_that("test player: constructor", {
  p <- Player$new("Michael")
  expect_equal(p$getName(), "Michael")
  expect_equal(p$getCoins(), 0)
})

test_that("test player: addCoins", {
  p <- Player$new("Michael")
  p$addCoins(10)
  expect_equal(p$getCoins(), 10)
})


