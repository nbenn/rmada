
#include <testthat.h>
#include <rmada/mem.h>

namespace bip = boost::interprocess;

context("shared memory") {

  struct shm_remove {
     shm_remove() { bip::shared_memory_object::remove("shared_memory"); }
     ~shm_remove(){ bip::shared_memory_object::remove("shared_memory"); }
  } remover;

  SharedMemory mem("shared_memory", 4096);

  test_that("initialization state") {
    expect_error([&](){
      bip::shared_memory_object shm(bip::create_only, "shared_memory",
          bip::read_write);
    }());
    expect_true(mem.is_attached());
    expect_true(mem.get_size() == 4096);
    expect_error([&](){
      SharedMemory shm("shared_memory", 8192);
    }());
  }

  test_that("at/detaching") {
    mem.attach();
    expect_true(mem.is_attached());
    mem.detach();
    expect_false(mem.is_attached());
    expect_true(mem.get_address() != nullptr);
    expect_true(mem.is_attached());
  }

  test_that("resizing") {
    mem.detach();
    // detached state
    mem.resize(8192);
    expect_true(mem.get_size() == 8192);
    expect_false(mem.is_attached());
    mem.attach();
    // attached state
    mem.resize(12288);
    expect_true(mem.get_size() == 12288);
    expect_false(mem.is_attached());
  }

  test_that("removing") {
    mem.remove();
    expect_false(mem.is_attached());
    expect_error(mem.get_address());
    expect_error(mem.get_size());
    expect_error(mem.remove());
  }
}

context("file backed memory") {

  std::string file_name = "file_backed_memory";

  struct file_remove {
    file_remove(std::string name) : fn(name) {}
    ~file_remove(){ bip::file_mapping::remove(fn.c_str()); }
    std::string fn;
  } remover(file_name);

  FileMemory mem(file_name, 4096);

  test_that("initialization state") {
    expect_true(mem.is_attached());
    expect_true(mem.get_size() == 4096);
    expect_error([&](){
      FileMemory shm(file_name, 8192);
    }());
  }

  test_that("at/detaching") {
    mem.attach();
    expect_true(mem.is_attached());
    mem.detach();
    expect_false(mem.is_attached());
    expect_true(mem.get_address() != nullptr);
    expect_true(mem.is_attached());
  }

  test_that("resizing") {
    mem.detach();
    // detached state
    mem.resize(8192);
    expect_true(mem.get_size() == 8192);
    expect_false(mem.is_attached());
    mem.attach();
    // attached state
    mem.resize(12288);
    expect_true(mem.get_size() == 12288);
    expect_false(mem.is_attached());
  }

  test_that("removing") {
    mem.remove();
    expect_false(mem.is_attached());
    expect_error(mem.get_address());
    expect_error(mem.get_size());
    expect_error(mem.remove());
  }

}
