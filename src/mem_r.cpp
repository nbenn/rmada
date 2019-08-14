// Copyright (C) 2019  Nicolas Bennett

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.

// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.

// You should have received a copy of the GNU General Public License along
// with this program. If not, see <http://www.gnu.org/licenses/>.

#include <rmada/mem.hpp>
#include <rmada/dispatch_type.hpp>
#include <rmada/utils.hpp>

template <typename L>
struct MemInit
{
  SEXP operator()(std::string name, std::size_t n_elem)
  {
    using mem = mp11::mp_at_c<L, 0>;
    using dat = mp11::mp_at_c<L, 1>;
    auto ind = std::size_t{i_form_num_type<dat>::value};
    auto res = new mem(name, n_elem * sizeof(dat));
    return Rcpp::XPtr<mem>(res, true, Rcpp::wrap(ind));
  }
};

// [[Rcpp::export]]
SEXP mem_init(std::string name, std::size_t n_elem, std::size_t data_type,
    std::size_t mem_type)
{
  using mem_data_types = mp11::mp_product<mp11::mp_list, mem_types, num_types>;
  auto ind = mem_type * std::size_t{mp11::mp_size<num_types>::value} +
      data_type;
  return dispatch_type<mem_data_types, MemInit>(ind, name, n_elem);
}

// [[Rcpp::export]]
void mem_attach(SEXP mem)
{
  xptr<Memory>(mem)->attach();
}

// [[Rcpp::export]]
void mem_detach(SEXP mem)
{
  xptr<Memory>(mem)->detach();
}

// [[Rcpp::export]]
bool is_mem_attached(SEXP mem)
{
  return xptr<Memory>(mem)->is_attached();
}

template <typename T>
struct MemAddress
{
  SEXP operator()(SEXP mem)
  {
    T* res = static_cast<T*>(xptr<Memory>(mem)->get_address());
    auto ind = std::size_t{i_form_num_type<T>::value};
    return Rcpp::XPtr<T>(res, false, Rcpp::wrap(ind));
  }
};

// [[Rcpp::export]]
SEXP get_mem_address(SEXP mem)
{
  return dispatch_mem<MemAddress>(mem);
}

template <typename T>
struct MemLength
{
  std::size_t operator()(SEXP mem)
  {
    return xptr<Memory>(mem)->get_size() / sizeof(T);
  }
};

// [[Rcpp::export]]
std::size_t get_mem_length(SEXP mem)
{
  return dispatch_mem<MemLength>(mem);
}

// [[Rcpp::export]]
std::string get_mem_id(SEXP mem)
{
  return xptr<Memory>(mem)->get_id();
}

// [[Rcpp::export]]
void mem_remove(SEXP mem)
{
  xptr<Memory>(mem)->remove();
}

template <typename T>
struct MemResize
{
  void operator()(SEXP mem, std::size_t n_elem)
  {
    xptr<Memory>(mem)->resize(n_elem * sizeof(T));
  }
};

// [[Rcpp::export]]
void mem_resize(SEXP mem, std::size_t n_elem)
{
  dispatch_mem<MemResize>(mem, n_elem);
}
