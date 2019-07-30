
#include <RcppArmadillo.h>

#include <rmada/mem.h>
#include <rmada/types.h>

template <typename DAT, typename MEM>
SEXP init_mem(std::string name, std::size_t length) {
  MEM* res = new MEM(name, length * sizeof(DAT));
  return Rcpp::XPtr<MEM>(res);
}

#define INIT_SHARED_MEM(TYPE) \
  return init_mem<TYPE, SharedMemory>(name, length);
#define INIT_FILE_MEM(TYPE) \
  return init_mem<TYPE, FileMemory>(name, length);

// [[Rcpp::export]]
SEXP init_mem(std::string name, std::size_t length, int data_type,
    std::string mem_type) {

  /*
    ideally this would be (auto)-extensible
     - do some like arma with ARMA_INCFILE_WRAP
     - https://stackoverflow.com/a/582456/3855417
  */

  if (mem_type == "SharedMemory") {
    DISPATCH_DATA_TYPE(INIT_SHARED_MEM)
  } else if (mem_type == "FileMemory") {
    DISPATCH_DATA_TYPE(INIT_FILE_MEM)
  } else {
    throw Rcpp::exception("Unsupported memory type.");
  }
}

// [[Rcpp::export]]
void mem_attach(Rcpp::XPtr<Memory> mem) {
  mem->attach();
}

// [[Rcpp::export]]
void mem_detach(Rcpp::XPtr<Memory> mem) {
  mem->detach();
}

// [[Rcpp::export]]
bool is_mem_attached(Rcpp::XPtr<Memory> mem) {
  return mem->is_attached();
}

template <typename T>
SEXP get_mem_address(Rcpp::XPtr<Memory> mem) {
  T* res = static_cast<T*>(mem->get_address());
  return Rcpp::XPtr<T>(res, false);
}

#define GET_MEM_ADDRESS(TYPE) return get_mem_address<TYPE>(mem);

// [[Rcpp::export]]
SEXP get_mem_address(Rcpp::XPtr<Memory> mem, int data_type) {
  DISPATCH_DATA_TYPE(GET_MEM_ADDRESS)
}

template <typename T>
int get_mem_length(Rcpp::XPtr<Memory> mem) {
  return mem->get_size() / sizeof(T);
}

#define GET_MEM_LENGTH(TYPE) return get_mem_length<TYPE>(mem);

// [[Rcpp::export]]
int get_mem_length(Rcpp::XPtr<Memory> mem, int data_type) {
  DISPATCH_DATA_TYPE(GET_MEM_LENGTH)
}

// [[Rcpp::export]]
std::string get_mem_id(Rcpp::XPtr<Memory> mem) {
  return mem->get_id();
}

// [[Rcpp::export]]
void mem_remove(Rcpp::XPtr<Memory> mem) {
  mem->remove();
}

template <typename T>
void mem_resize(Rcpp::XPtr<Memory> mem, std::size_t length) {
  mem->resize(length * sizeof(T));
}

#define MEM_RESIZE(TYPE) return mem_resize<TYPE>(mem, length);

// [[Rcpp::export]]
void mem_resize(Rcpp::XPtr<Memory> mem, std::size_t length, int data_type) {
  DISPATCH_DATA_TYPE(MEM_RESIZE)
}
