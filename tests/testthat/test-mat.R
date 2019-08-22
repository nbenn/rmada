
nrow <- 6L
ncol <- 4L

mem_id <- "shmem_test_mat"
data_type <- "int"
mem_type <- "SharedMemory"

sh_mat <- mat$new(nrow, ncol, id = mem_id, data_type = data_type,
                  mem_type = mem_type)

test_that("matrix instantiation", {
  expect_is(sh_mat, "mat")
  expect_is(sh_mat, "memory")
  expect_equal(nrow(sh_mat), nrow)
  expect_equal(ncol(sh_mat), ncol)
  expect_equal(length(sh_mat), nrow * ncol)
})

test_that("value initialization", {
  sh_mat$fill(0L)
  expect_equal(sh_mat$submat(1L, 1L, nrow, ncol), matrix(0L, nrow, ncol))
  sh_mat$fill("zeros")
  expect_equal(sh_mat$submat(1L, 1L, nrow, ncol), matrix(0L, nrow, ncol))
  sh_mat$fill(1L)
  expect_equal(sh_mat$submat(1L, 1L, nrow, ncol), matrix(1L, nrow, ncol))
  sh_mat$fill("ones")
  expect_equal(sh_mat$submat(1L, 1L, nrow, ncol), matrix(1L, nrow, ncol))
  sh_mat$fill(7L)
  expect_equal(sh_mat$submat(1L, 1L, nrow, ncol), matrix(7L, nrow, ncol))
  sh_mat$fill("eye")
  expect_equal(sh_mat$submat(1L, 1L, nrow, ncol),
    rbind(diag(ncol), matrix(0L, nrow - ncol, ncol)))
})
