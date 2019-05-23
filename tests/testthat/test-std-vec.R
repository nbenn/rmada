context("test-std-vec")

test_that("demo test", {

  col <- new(rmada:::col, 10L)
  expect_equal(col$length, 10L)

  mat <- new(rmada:::mat, 10L, 10L)
  expect_equal(mat$length, 100L)
})
