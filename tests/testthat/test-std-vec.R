context("test-std-vec")

test_that("demo test", {

  v <- new(rmada:::vec)
  data <- 1:10
  v$assign(data)
  v[[3]] <- v[[3]] + 1

  data[[4]] <- data[[4]] + 1

  expect_identical(v$as.vector(), data)
})
