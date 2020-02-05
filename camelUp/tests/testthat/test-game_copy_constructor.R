test_that("test game: copy constructor runs", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  h <- Game$new(g)
  expect_equal(TRUE, TRUE)
})
#
test_that("test game: copied game getCamelDF", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  h <- Game$new(g)
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Space = c(1, 2, 2, 3, 1),
                        Height = c(1, 1, 2, 1, 2))
  expect_equal(h$getCamelDF(), true_df)
})

test_that("test game: copied game getCamelDF", {
  set.seed(1)
  g <- Game$new(19, 3, TRUE)
  h <- Game$new(g)
  h$takeTurnMove()
  true_df <- data.frame(Color = c("Green", "White", "Yellow", "Orange", "Blue"),
                        Space = c(1, 2, 2, 3, 1),
                        Height = c(1, 1, 2, 1, 2))
  expect_equal(g$getCamelDF(), true_df)
})
