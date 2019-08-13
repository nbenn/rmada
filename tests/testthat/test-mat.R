
nrow <- 6L
ncol <- 4L

mem_id <- "shmem_test"
data_type <- "int"
mem_type <- "SharedMemory"

sh_mat <- mat$new(nrow, ncol, id = mem_id, data_type = data_type,
                  mem_type = mem_type)

test_that("matrix instantiation", {
  expect_is(sh_mat, "mat")
  expect_is(sh_mat, "memory")
  expect_equal(nrow(sh_mat), nrow)
  expect_equal(ncol(sh_mat), ncol)
})

