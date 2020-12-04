context("genData")
library(CamelUp)

test_that("test genData: random choices", {
  genData(1, "agent", getRandomChoiceAgent, "agent", getRandomChoiceAgent)
  expect_equal(TRUE, TRUE)
})


test_that("test genData: random choices n times", {
  genDataNTimes(10, "agent", getRandomChoiceAgent, "agent", getRandomChoiceAgent)
  expect_equal(TRUE, TRUE)
})


test_that("test genData: random choices n times", {
  genDataNTimes(10, "agent", getRandomChoiceAgent, "agent", getRandomChoiceAgent)
  expect_equal(TRUE, TRUE)
})


test_that("test genData: random choices n times", {
  genRandomDataNTimes(10)
  expect_equal(TRUE, TRUE)
})

test_that("test genData: random choices n times", {
  genLegBetMaxEVDataNTimes(5)
  expect_equal(TRUE, TRUE)
})
