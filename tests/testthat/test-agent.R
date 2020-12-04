context("agent")
library(CamelUp)
test_that("test agent: constructor", {
  a <- Agent$new("Me")
  expect_equal(a$getName(), "Me")
})

test_that("test agent: join game", {
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  expect_equal(TRUE, TRUE)
})


test_that("test agent: join game", {
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  g2 <- a$getGame()
  expect_equal(g$getCamelDF(), g2$getCamelDF())
})

test_that("test agent: get random choice", {
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  expect_equal(TRUE, a$getRandomChoice() %in% g$getTurnOptions())
})


test_that("test agent: take turn move", {
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  a$takeTurn("move")
  expect_equal(TRUE, TRUE)
})

test_that("test agent: place leg bet yellow", {
  # leg bet is made
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  a$takeTurn("legBetYellow")
  expect_equal(g$getNMadeLegBets(), 1)
})


test_that("test agent: place overall winner bet yellow", {
  # leg bet is made
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  a$takeTurn("overallWinnerYellow")
  expect_equal(g$getNOverallWinnersPlaced(), 1)
})


test_that("test agent: simulate to end of leg", {
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  simData <- a$simulateLeg()
  expect_equal(nrow(simData), 500)
})


test_that("test agent: getLegBetMaxEV", {
  set.seed(1)
  g <- Game$new(19, 2, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  expect_equal(a$getLegBetMaxEV(), "Yellow")
})

