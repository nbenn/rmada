context("test-std-vec")

test_that("demo test", {

  x <- mat$new(10, 10)
  expect_is(x, "mat")
  expect_equal(nrow(x), 10)
  expect_equal(ncol(x), 10)
})
