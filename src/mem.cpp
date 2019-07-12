
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

namespace bip = boost::interprocess;
using namespace std;

class Memory {

public:

  virtual void attach() = 0;
  virtual void detach() = 0;

  virtual void* get_address() = 0;
  virtual size_t get_size() = 0;

  virtual void remove() = 0;

  //virtual void resize(size_t new_size) = 0;

};

class SharedMemory: public Memory {

public:

  SharedMemory(string id, size_t length) :
      mem(bip::open_or_create, id.c_str(), bip::read_write) {
    mem.truncate(length);
  }

  void attatch() {
    map = bip::mapped_region(mem, bip::read_write);
  }

  void detatch() {
    map = bip::mapped_region();
  }

  void* get_address() {
    return map.get_address();
  }

  size_t get_size() {
    return map.get_size();
  }

  void remove() {
    mem.remove(mem.get_name());
  }

private:

  bip::shared_memory_object mem;
  bip::mapped_region map;

};
