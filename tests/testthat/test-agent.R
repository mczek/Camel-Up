context("agent")
library(CamelUp)
test_that("test agent: constructor", {
  a <- Agent$new("Me")
  expect_equal(a$getName(), "Me")
})

test_that("test agent: update knowledge", {
  a <- Agent$new("Me")
  a$updateKnowledge(mtcars)
  expect_equal(0, sum(a$getKnowledge() != mtcars))
})

test_that("test agent: getRandomChoice", {
  g <- Game$new(19, 3, TRUE)
  a <- Agent$new("Me")
  a$joinGame(g)
  expect_equal(a$randomChoice(), "move")
})
