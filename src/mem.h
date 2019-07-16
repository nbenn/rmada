
#ifndef RMADA_MEM_H
#define RMADA_MEM_H

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/filesystem.hpp>

class Memory {

public:

  virtual void attach() = 0;
  virtual void detach() = 0;
  virtual bool is_attached() = 0;

  virtual void* get_address() = 0;
  virtual std::size_t get_size() = 0;

  virtual void remove() = 0;

  virtual void resize(std::size_t) = 0;

};

class SharedMemory: public Memory {

public:

  SharedMemory(std::string, std::size_t);

  void attach();
  void detach();
  bool is_attached();

  void* get_address();
  std::size_t get_size();

  void remove();

  void resize(std::size_t);

private:

  boost::interprocess::shared_memory_object mem;
  boost::interprocess::mapped_region map;

};

class FileMemory: public Memory {

public:

  FileMemory(std::string, std::size_t);

  void attach();
  void detach();
  bool is_attached();

  void* get_address();
  std::size_t get_size();

  void remove();

  void resize(std::size_t);

private:

  boost::interprocess::file_mapping mem;
  boost::interprocess::mapped_region map;

  boost::filesystem::path file_path();

};

#endif /* RMADA_MEM_H */
