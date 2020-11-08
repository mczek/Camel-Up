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
