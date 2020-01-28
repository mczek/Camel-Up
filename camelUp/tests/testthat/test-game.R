test_that("test game: constructor", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)

  df <- g$getPurseDF()
  true_df <- data.frame(Player = paste(rep("Player", 3), 0:2),
                        Coins = rep(0, 3))

  expect_equal(df, true_df)


  df <- g$getCamelDF()
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Space = c(1, 2, 2, 3, 1),
                        Height = c(1, 1, 2, 1, 2))
  expect_equal(df, true_df)

  expect_equal(g$getRanking(), c("Orange", "Yellow", "White", "Blue", "Green"))


  df <- g$getLegBetDF()
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Value = rep(5,5),
                        nBets = rep(3, 5))
  expect_equal(df, true_df)
})

test_that("test game: takeTurnMove", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  g$takeTurnMove()
  df <- g$getPurseDF()
  true_df <- data.frame(Player = paste(rep("Player", 3), 0:2),
                        Coins = c(1, 0, 0))

  df <- g$getCamelDF()
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Space = c(1, 2, 2, 3, 4),
                        Height = c(1, 1, 2, 1, 1))
  expect_equal(df, true_df)


})

test_that("test game: takeTurnLegBet", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  g$takeTurnLegBet("Blue")
  df <- g$getLegBetDF()
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Value = c(rep(5,4), 3),
                        nBets = c(rep(3,4), 2))
  expect_equal(df, true_df)
})

test_that("test game: evaluateBets", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  g$takeTurnLegBet("Orange")
  g$takeTurnLegBet("Orange")
  expect_equal(g$getNMadeLegBets(), 2)

  g$evaluateLegBets()
  df <- g$getPurseDF()
  true_df <- data.frame(Player = paste(rep("Player", 3), 0:2),
                        Coins = c(8, 0, 0))
  expect_equal(df, true_df)
})

test_that("something", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  h <- Game$new(g)
  h$takeTurnMove()

  df <- g$getCamelDF()
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Space = c(1, 2, 2, 3, 1),
                        Height = c(1, 1, 2, 1, 2))
  expect_equal(df, true_df)

})
