
#include <RcppArmadillo.h>

#include "types.h"

template <typename DAT, typename MEM>
SEXP init_mem(std::string name, std::size_t length) {
  MEM* mem = new MEM(name, length * sizeof(DAT));
  return(Rcpp::XPtr<MEM>(mem, true));
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
