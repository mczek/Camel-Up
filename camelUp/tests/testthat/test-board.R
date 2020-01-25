test_that("test board: constructor", {
  b <- Board$new(19, FALSE)
  expect_equal(b$getNDiceRemaining(), 5)
  expect_equal(b$getNCamels(), 5)
})

test_that("test board: initCamels", {
  set.seed(1)
  b <- Board$new(19, TRUE)

  df <- b$getCamelDF()
  true_df <- data.frame(x = c("Green", "White", "Yellow", "Orange", "Blue"),
                        y = c(1, 2, 2, 3, 1),
                        z = c(1, 1, 2, 1, 2))

  expect_equal(df, true_df)
})

test_that("test board: moveTurn", {
  set.seed(1)
  b <- Board$new(19, TRUE)

  df <- b$getCamelDF()
  true_df <- data.frame(x = c("Green", "White", "Yellow", "Orange", "Blue"),
                        y = c(1, 2, 2, 3, 1),
                        z = c(1, 1, 2, 1, 2))

  expect_equal(df, true_df)
})
