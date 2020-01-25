test_that("test board constructor", {
  b <- Board$new(19)
  expect_equal(b$getNDiceRemaining(), 5)
  expect_equal(b$getNCamels(), 5)
})

test_that("test space", {
  set.seed(1)
  b <- Board$new(19)
  b$getCamelDF()
})
