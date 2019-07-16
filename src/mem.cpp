
#include "mem.h"

namespace bip = boost::interprocess;
namespace fs = boost::filesystem;

SharedMemory::SharedMemory(std::string id, std::size_t length) {

  try {

    mem = bip::shared_memory_object(bip::create_only, id.c_str(),
        bip::read_write);
    mem.truncate(length);

  } catch(const bip::interprocess_exception& er) {

    if (er.get_native_error() == boost::system::errc::file_exists) {
      mem = bip::shared_memory_object(bip::open_only, id.c_str(),
          bip::read_write);
    } else {
      throw;
    }
  }

  if (get_size() != length) {
    throw std::runtime_error("Could not set up a shared memory segment of "
        "the requested size.");
  }
}

void SharedMemory::attach() {
  map = bip::mapped_region(mem, bip::read_write);
}

void SharedMemory::detach() {
  map = bip::mapped_region();
}

bool SharedMemory::is_attached() {
  return map.get_address() != nullptr;
}

void* SharedMemory::get_address() {

  if (!is_attached()) {
    attach();
  }

  return map.get_address();
}

std::size_t SharedMemory::get_size() {

  bip::offset_t size;

  if (!mem.get_size(size)) {
    throw std::runtime_error("Could not obtain size of shared memory "
        "segment.");
  }

  if (size < 0) {
    throw std::runtime_error("Determined size of shared memory segment to be "
        "negative.");
  }

  return size;
}

void SharedMemory::remove() {

  if (is_attached()) {
    detach();
  }

  if (!mem.remove(mem.get_name())) {
    throw std::runtime_error("Could not remove shared memory segment.");
  }

  mem = bip::shared_memory_object();
}

void SharedMemory::resize(std::size_t new_size) {

  if (is_attached()) {
    detach();
  }

  mem.truncate(new_size);
}

FileMemory::FileMemory(std::string file_path, std::size_t length) {

  fs::path path(file_path);

  if (fs::exists(path)) {
    if (!fs::is_regular_file(path)) {
      throw std::runtime_error("File path already exists, but is not a file.");
    }
  } else {
    {
      std::ofstream file(file_path);
      fs::resize_file(file_path, length);
    }
  }

  if (fs::file_size(file_path) != length) {
    throw std::runtime_error("File-size does not correspond to requested "
        "size.");
  }

  mem = bip::file_mapping(file_path.c_str(), bip::read_write);
}

void FileMemory::attach() {
  map = bip::mapped_region(mem, bip::read_write);
}

void FileMemory::detach() {
  map = bip::mapped_region();
}

bool FileMemory::is_attached() {
  return map.get_address() != nullptr;
}

void* FileMemory::get_address() {

  if (!is_attached()) {
    attach();
  }

  return map.get_address();
}

std::size_t FileMemory::get_size() {

  auto size = fs::file_size(file_path());

  if (size < 0) {
    throw std::runtime_error("Could not determine file size.");
  }

  return size;
}

void FileMemory::remove() {

  if (is_attached()) {
    detach();
  }

  if (!mem.remove(file_path().c_str())) {
    throw std::runtime_error("Could not remove memory mapped file.");
  }

  mem = bip::file_mapping();
}

void FileMemory::resize(std::size_t new_size) {

  if (is_attached()) {
    detach();
  }

  fs::resize_file(file_path(), new_size);
}

fs::path FileMemory::file_path() {
  return fs::path(mem.get_name());
}
