
#include <testthat.h>
#include "mem.h"

namespace bip = boost::interprocess;

context("shared memory") {

  SharedMemory mem("shared_memory", 4096);

  test_that("initialization state") {
    expect_true(mem.get_address() == nullptr);
    expect_true(mem.get_size() == 0);
  }

  test_that("at/detatching") {
    mem.attatch();
    expect_false(mem.get_address() == nullptr);
    expect_true(mem.get_size() == 4096);
    mem.detatch();
    expect_true(mem.get_address() == nullptr);
    expect_true(mem.get_size() == 0);
  }

  test_that("resizing") {
    mem.detatch();
    // detatched state
    mem.resize(8192);
    expect_true(mem.get_address() == nullptr);
    expect_true(mem.get_size() == 0);
    mem.attatch();
    expect_true(mem.get_size() == 8192);
    // attatched state
    mem.resize(12288);
    expect_true(mem.get_address() == nullptr);
    expect_true(mem.get_size() == 0);
    mem.attatch();
    expect_true(mem.get_size() == 12288);
  }

  test_that("removing") {
    mem.remove();
    expect_true(mem.get_address() == nullptr);
    expect_true(mem.get_size() == 0);
    expect_error(mem.remove());
  }

}
