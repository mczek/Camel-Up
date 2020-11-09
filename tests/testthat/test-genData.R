context("genData")
library(CamelUp)

test_that("test genData: random choices", {
  genRandomData(1)
  expect_equal(TRUE, TRUE)
})


test_that("test genData: random choices n times", {
  genRandomDataNTimes(10)
  expect_equal(TRUE, TRUE)
})
