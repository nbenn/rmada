// Copyright (C) 2019  Nicolas Bennett

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <rmada/mem.h>
#include <rmada/dispatch_type.h>

#include <Rcpp.h>

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
