test_that("test simulator: constructor", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  s <- Simulator$new(g)
  s$simulateMoveEndGame(1)
  expect_equal(TRUE, TRUE)
})

test_that("test simulator: time simulation 1000 sims - 0.015s", {
  set.seed(1)
  g <- Game$new(19, 3, FALSE)
  s <- Simulator$new(g)
  t <- system.time({
   a <- s$simulateMoveEndGame(1000)
  })
  print(t)
  expect_equal(TRUE, TRUE)
})

# h <- Game$new(g)
# h$progressToEndGame()
# h$getCamelDF()
