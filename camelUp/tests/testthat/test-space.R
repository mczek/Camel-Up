test_that("test space constructor", {
  s <- Space$new(5)
  expect_equal(s$getPosition(), 5)
  expect_equal(s$getNCamels(), 0)
})
