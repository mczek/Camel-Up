context("testObjects.R")


### TEST STACK OBJECT


test_that("Stack: n = 0", {
  x <- stack$new()
  expect_equal( x$n, 0)
  expect_equal( x$top(), NA)
  expect_error( x$pop())


})


test_that("Stack: n = 1", {
  x <- stack$new()
  x$push(5)

  expect_equal( x$n, 1)
  expect_equal( x$top(), 5)
  expect_equal( x$pop(), 5)


})



test_that("Stack: n = 2", {
  x <- stack$new()
  x$push(5)
  x$push(6)

  expect_equal( x$n, 2)
  expect_equal( x$top(), 6)
  expect_equal( x$pop(), 6)

})




test_that("Camel: initialize",{
  # TEST CAMEL OBJECT
  x <- camel$new("blue", 1, 1)

  expect_equal(x$color, "blue")
  expect_equal(x$position, 1)
  expect_equal(x$index, 1)
})

test_that("Camel: getColor",{
  x <- camel$new("blue", 1, 1)

  expect_equal(x$getColor(), "blue")
})

test_that("Camel: move",{
  x <- camel$new("blue", 1, 1)

  x$move(1)
  expect_equal(x$position, 2)
  x$move(2)
  expect_equal(x$position, 4)
})

test_that("Camel: duplicate",{
  x <- camel$new("blue", 1, 1)
  y <- x$duplicate()
  expect_equal(all.equal(x,y), TRUE)
})



test_that("Space: initialize",{
  ### TEST SPACE OBJECT
  x <- space$new()

  expect_equal(class(x$camels), c("Stack", "R6"))
  expect_equal(all.equal(x$camels, stack$new()), TRUE)
  expect_equal(x$plus.tile, FALSE)
  expect_equal(x$minus.tile, FALSE)
  expect_equal(x$tile.placed.by, NA)
})

test_that("Space: push.camel",{
  x <- space$new()
  y <- camel$new("blue", 1, 1)
  x$push.camel(y)
  expect_equal(x$camels$n, 1)

})

test_that("Space: pop.camel",{
  x <- space$new()
  y <- camel$new("blue", 1, 1)
  x$push.camel(y)
  expect_equal(all.equal(x$camels$pop(), y), TRUE)
})

test_that("Space: place.tile",{
  x <- space$new()
  x$place.tile("minus")
  expect_equal(x$minus.tile, TRUE)
  expect_equal(x$plus.tile, FALSE)

  x <- space$new()
  x$place.tile("plus")
  expect_equal(x$plus.tile, TRUE)
  expect_equal(x$minus.tile, FALSE)
})

test_that("Space: duplicate",{
  x <- space$new()
  expect_equal(all.equal(x, x$duplicate()), TRUE)

  y <- camel$new("blue", 1, 1)
  x$push.camel(y)
  expect_equal(isTRUE(all.equal(x, x$duplicate())), TRUE)
})

test_that("Die: initialize",{
  x <- die$new("blue")
  expect_equal(x$color, "blue")
})

test_that("Die: roll",{
  x <- die$new("blue")
  set.seed(1)
  expect_equal(x$roll(), 1)
})

test_that("Die: duplicate",{
  x <- die$new("blue")
  expect_equal(isTRUE(all.equal(x, x$duplicate())), TRUE)
})

test_that("Leg Bet: initialize",{
  x <- bet$new("blue", 5)
  expect_equal(x$color, "blue")
  expect_equal(x$value, 5)
})

test_that("Leg Bet: duplicate",{
  x <- bet$new("blue", 5)
  expect_equal(isTRUE(all.equal(x, x$duplicate())), TRUE)
})

test_that("Overall Bet: initialize",{
  x <- overall.bet$new("blue", "Alex")
  expect_equal(x$color, "blue")
  expect_equal(x$player, "Alex")
})

test_that("Overall Bet: duplicate",{
  x <- overall.bet$new("blue", "Alex")
  expect_equal(isTRUE(all.equal(x, x$duplicate())), TRUE)
})


test_that("Board: initialize",{
  s <- system$new(2, c("Alex", "Tom"))
  x <- board$new(s)
  expect_equal(x$system, s)
  expect_equal(length(x$spaces), 19)

  expect_equal(class(x$y.bets), c("Stack", "R6"))
  expect_equal(class(x$o.bets), c("Stack", "R6"))
  expect_equal(class(x$b.bets), c("Stack", "R6"))
  expect_equal(class(x$g.bets), c("Stack", "R6"))
  expect_equal(class(x$w.bets), c("Stack", "R6"))

  expect_equal(class(x$winner.bets), c("Stack", "R6"))
  expect_equal(class(x$loser.bets), c("Stack", "R6"))

  expect_equal(length(x$tot.camels), 5)
  expect_equal(length(x$dice.left), 5)
})

test_that("Board: choose.die", {
  s <- system$new(2, c("Alex", "Tom"))
  x <- board$new(s)
  d <- x$choose.die()

  expect_equal(d$color, "Green")
  expect_equal(length(x$dice.rolled), 1)
  expect_equal(length(x$dice.left), 4)
})
