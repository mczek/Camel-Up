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
                        Value = rep(5,5))
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

test_that("test game: getLegBetDF", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  g$takeTurnLegBet("Blue")
  g$getLegBetDF()


})
