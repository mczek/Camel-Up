test_that("test die", {
  d <- Die$new("Blue")
  expect_equal(d$getColor(), "Blue")
  expect_equal(d$getValue(), 0)
  expect_true(d$roll() %in% 1:3)
  expect_true(d$roll() %in% 1:3)
  expect_true(d$roll() %in% 1:3)
  expect_true(d$roll() %in% 1:3)
})
