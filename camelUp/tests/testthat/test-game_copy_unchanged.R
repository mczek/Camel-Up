test_that("test game: copy constructor", {
  g <- Game$new(19, 3, TRUE)
  df <- g$getCamelDF()
  h <- Game$new(g)
  expect_equal(df, g$getCamelDF())
  })

test_that("test game: copy constructor", {
  g <- Game$new(19, 3, TRUE)
  h <- Game$new(g)
  k <- Game$new(g)
  expect_equal(TRUE, TRUE)
})
