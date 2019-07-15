
#ifndef RMADA_MEM_H
#define RMADA_MEM_H

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

class Memory {

public:

  virtual void attatch() = 0;
  virtual void detatch() = 0;

  virtual void* get_address() = 0;
  virtual std::size_t get_size() = 0;

  virtual void remove() = 0;

  virtual void resize(std::size_t) = 0;

};

class SharedMemory: public Memory {

public:

  SharedMemory(std::string, std::size_t);

  void attatch();
  void detatch();

  void* get_address();
  std::size_t get_size();

  void remove();

  void resize(std::size_t);

private:

  boost::interprocess::shared_memory_object mem;
  boost::interprocess::mapped_region map;

};

#endif /* RMADA_MEM_H */
