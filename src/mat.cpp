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
#include <rmada/type_dispatch.hpp>
#include <rmada/utils.hpp>

template <typename T>
struct MatInit
{
  SEXP operator()(Rcpp::XPtr<Memory> mem, arma::uword n_rows, arma::uword
      n_cols)
  {
    using arma_t = arma::Mat<T>;
    T* ptr = static_cast<T*>(mem->get_address());
    auto res = new arma_t(ptr, n_rows, n_cols, false, true);
    auto tag = create_tag(std::size_t{i_form_arma_type<arma_t>::value},
        std::size_t{i_form_num_type<T>::value});
    return Rcpp::XPtr<arma_t>(res, true, Rcpp::wrap(tag));
  }
};

// [[Rcpp::export]]
SEXP mat_init(SEXP mem, arma::uword n_rows, arma::uword n_cols,
    std::size_t data_type)
{
  if (data_type != get_tag_val(mem, "num_type"))
  {
    throw std::runtime_error("Data types do not match.");
  }

  return dispatch_num_type<MatInit>(data_type, Rcpp::XPtr<Memory>(mem),
      n_rows, n_cols);
}
