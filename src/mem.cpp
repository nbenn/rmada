
#include "mem.h"

#include <boost/system/error_code.hpp>

#include <cstdio>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace bip = boost::interprocess;

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

  map = bip::mapped_region(mem, bip::read_write);
}

void SharedMemory::attach() {

  if (!is_attached()) {
    map = bip::mapped_region(mem, bip::read_write);
  }
}

void SharedMemory::detach() {

  if (is_attached()) {
    map = bip::mapped_region();
  }
}

bool SharedMemory::is_attached() {
  return map.get_address() != nullptr;
}

void* SharedMemory::get_address() {

  attach();

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

  detach();

  if (!mem.remove(mem.get_name())) {
    throw std::runtime_error("Could not remove shared memory segment.");
  }

  mem = bip::shared_memory_object();
}

void SharedMemory::resize(std::size_t new_size) {

  detach();

  mem.truncate(new_size);
}

FileMemory::FileMemory(std::string file_path, std::size_t length) {

  if (!file_exists(file_path)) {
    create_file(file_path);
    resize_file(file_path, length);
  }

  if (file_size(file_path) != length) {
    throw std::runtime_error("File-size does not correspond to requested "
        "size.");
  }

  mem = bip::file_mapping(file_path.c_str(), bip::read_write);
  map = bip::mapped_region(mem, bip::read_write);
}

void FileMemory::attach() {

  if (!is_attached()) {
    map = bip::mapped_region(mem, bip::read_write);
  }
}

void FileMemory::detach() {

  if (is_attached()) {
    map = bip::mapped_region();
  }
}

bool FileMemory::is_attached() {
  return map.get_address() != nullptr;
}

void* FileMemory::get_address() {

  attach();

  return map.get_address();
}

std::size_t FileMemory::get_size() {

  return file_size(file_path());
}

void FileMemory::remove() {

  detach();

  if (!mem.remove(file_path().c_str())) {
    throw std::runtime_error("Could not remove memory mapped file.");
  }

  mem = bip::file_mapping();
}

void FileMemory::resize(std::size_t new_size) {

  detach();

  resize_file(file_path(), new_size);
}

std::string FileMemory::file_path() {
  return std::string(mem.get_name());
}

bool file_exists(std::string file_path) {
  return std::ifstream(file_path).good();
}

std::size_t file_size(std::string file_path) {

  std::ifstream file(file_path, std::ios::ate | std::ios::binary);

  if (!std::ifstream(file_path).good()) {
    throw std::runtime_error("Can not determine file size.");
  }

  return file.tellg();
}

void create_file(std::string file_path) {

  if (file_exists(file_path)) {
    throw std::runtime_error("File already exists.");
  }

  std::ofstream outfile(file_path);
}

void resize_file(std::string file_path, std::size_t new_size) {

  if (!file_exists(file_path)) {
    throw std::runtime_error("Will not resize non existing file.");
  }

  auto file = std::fopen(file_path.c_str(), "r+");

  if (!file) {
    throw std::runtime_error("Can not open file.");
  }

  int fdesc = fileno(file);

#ifdef _WIN32

  HANDLE hand = static_cast<HANDLE> (&fdesc);
  LARGE_INTEGER size = {new_size};

  if (!SetFilePointerEx(hand, size, NULL, FILE_BEGIN)) {
    throw std::runtime_error("Could not set file size.");
  }

  if (!SetEndOfFile(hand)) {
    throw std::runtime_error("Could not resize file.");
  }

#else

  if (ftruncate(fdesc, new_size) != 0) {
    throw std::runtime_error("Could not resize file.");
  }

#endif

  std::fclose(file);
}
