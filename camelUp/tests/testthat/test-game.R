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
})
