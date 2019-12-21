test_that("test board constructor", {
  b <- Board$new(19)
  expect_equal(b$getNDiceRemaining(), 5)
  expect_equal(b$getNCamels(), 5)
})
