
#include "mem.h"

namespace bip = boost::interprocess;

SharedMemory::SharedMemory(std::string id, std::size_t length) :
    mem(bip::open_or_create, id.c_str(), bip::read_write),
    map() {

  std::size_t curr_size = get_size();

  if (curr_size == 0 && length > 0) {
    mem.truncate(length);
  } else if (curr_size != length) {
    throw std::runtime_error("Will not resize an existing shared memory "
        "segment without explicit call to resize().");
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

  return static_cast<std::size_t>(size);
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
