
#include "mem.h"

namespace bip = boost::interprocess;

SharedMemory::SharedMemory(std::string id, std::size_t length) :
    mem(bip::open_or_create, id.c_str(), bip::read_write) {

  mem.truncate(length);
}

void SharedMemory::attatch() {
  map = bip::mapped_region(mem, bip::read_write);
}

void SharedMemory::detatch() {
  map = bip::mapped_region();
}

void* SharedMemory::get_address() {
  return map.get_address();
}

std::size_t SharedMemory::get_size() {
  return map.get_size();
}

void SharedMemory::remove() {
  mem.remove(mem.get_name());
}

void SharedMemory::resize(std::size_t new_size) {

  if (get_address() != nullptr) {
    detatch();
  }

  mem.truncate(new_size);
}
