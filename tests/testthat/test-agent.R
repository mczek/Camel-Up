context("agent")
library(CamelUp)
test_that("test agent: constructor", {
  a <- Agent$new("Me")
  expect_equal(a$getName(), "Me")
})

