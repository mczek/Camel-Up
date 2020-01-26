test_that("test game: constructor", {
  g <- Game$new(19, 3, TRUE)

  df <- g$getPurseDF()
  true_df <- data.frame(Player = paste(rep("Player", 3), 0:2),
                        Coins = rep(0, 3))

  expect_equal(df, true_df)
})
