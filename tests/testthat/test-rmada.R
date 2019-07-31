
mem_len <- 10L
new_len <- 12L
mem_id <- "shmem_test"
data_type <- 8L
mem_type <- "SharedMemory"

shared_mem <- obj$new(mem_len, mem_id, data_type, mem_type)

test_that("shared memory object instantiation", {
  expect_is(shared_mem, "obj")
  expect_true(shared_mem$is_attached)
  expect_equal(shared_mem$length, mem_len)
  expect_equal(shared_mem$id, mem_id)
  expect_equal(shared_mem$data_type, data_type)
  expect_equal(shared_mem$mem_type, mem_type)
  expect_is(shared_mem$obj_ptr, "externalptr")
  expect_is(shared_mem$data_ptr, "externalptr")
  expect_false(identical(shared_mem$obj_ptr, methods::new("externalptr")))
  expect_false(identical(shared_mem$data_ptr, methods::new("externalptr")))
  expect_false(identical(shared_mem$obj_ptr, shared_mem$data_ptr))
})

test_that("shared memory object de/attaching", {
  expect_is(shared_mem$detach(), "obj")
  expect_false(shared_mem$is_attached)
  expect_is(shared_mem$attach(), "obj")
  expect_true(shared_mem$is_attached)
})

test_that("shared memory object resizing", {
  expect_is(shared_mem$resize(new_len), "obj")
  expect_equal(shared_mem$length, new_len)
  expect_is(shared_mem$resize(mem_len), "obj")
  expect_equal(shared_mem$length, mem_len)
})

mem_id <- tempfile()
mem_type <- "FileMemory"

file_mem <- obj$new(mem_len, mem_id, data_type, mem_type)

test_that("file backed memory object instantiation", {
  expect_is(file_mem, "obj")
  expect_true(file_mem$is_attached)
  expect_equal(file_mem$length, mem_len)
  expect_equal(file_mem$id, mem_id)
  expect_equal(file_mem$data_type, data_type)
  expect_equal(file_mem$mem_type, mem_type)
  expect_is(file_mem$obj_ptr, "externalptr")
  expect_is(file_mem$data_ptr, "externalptr")
  expect_false(identical(file_mem$obj_ptr, methods::new("externalptr")))
  expect_false(identical(file_mem$data_ptr, methods::new("externalptr")))
  expect_false(identical(file_mem$obj_ptr, file_mem$data_ptr))
})

test_that("file backed memory object de/attaching", {
  expect_is(file_mem$detach(), "obj")
  expect_false(file_mem$is_attached)
  expect_is(file_mem$attach(), "obj")
  expect_true(file_mem$is_attached)
})

test_that("file backed object resizing", {
  expect_is(file_mem$resize(new_len), "obj")
  expect_equal(file_mem$length, new_len)
  expect_is(file_mem$resize(mem_len), "obj")
  expect_equal(file_mem$length, mem_len)
})
