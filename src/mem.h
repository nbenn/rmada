
#ifndef RMADA_MEM_H
#define RMADA_MEM_H

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/file_mapping.hpp>

class Memory {

public:

  virtual void attach() = 0;
  virtual void detach() = 0;
  virtual bool is_attached() = 0;

  virtual void* get_address() = 0;
  virtual uintmax_t get_size() = 0;

  virtual void remove() = 0;

  virtual void resize(uintmax_t) = 0;

  virtual ~Memory() {}
};

class SharedMemory: public Memory {

public:

  SharedMemory(std::string, uintmax_t);

  void attach();
  void detach();
  bool is_attached();

  void* get_address();
  uintmax_t get_size();

  void remove();

  void resize(uintmax_t);

private:

  boost::interprocess::shared_memory_object mem;
  boost::interprocess::mapped_region map;

};

class FileMemory: public Memory {

public:

  FileMemory(std::string, uintmax_t);

  void attach();
  void detach();
  bool is_attached();

  void* get_address();
  uintmax_t get_size();

  void remove();

  void resize(uintmax_t);

private:

  boost::interprocess::file_mapping mem;
  boost::interprocess::mapped_region map;

  std::string file_path();

};

bool file_is_accessible(std::string);
uintmax_t file_size(std::string);
void create_file(std::string);
void resize_file(std::string, uintmax_t);

#endif /* RMADA_MEM_H */
