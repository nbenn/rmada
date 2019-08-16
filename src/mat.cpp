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
  SEXP operator()(SEXP mem, arma::uword n_rows, arma::uword n_cols)
  {
    using arma_t = arma::Mat<T>;
    T* ptr = static_cast<T*>(xptr<Memory>(mem)->get_address());
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

  return dispatch_num_type<MatInit>(data_type, mem, n_rows, n_cols);
}

template <typename T>
struct MatSubset
{
  SEXP operator()(SEXP x, arma::uvec i, arma::uvec j)
  {
    arma::Mat<T> res = xptr<arma::Mat<T>>(x)->submat(i, j);
    return Rcpp::wrap(res);
  }
};

// [[Rcpp::export]]
SEXP mat_subset(SEXP x, arma::uvec i, arma::uvec j)
{
  return dispatch_num_obj<MatSubset>(x, i - 1, j - 1);
}

template <typename T>
struct subview_container
{
  T view;
  subview_container(T subv): view(subv) {}
};

template <typename T>
struct MatSubview
{
  SEXP operator()(SEXP x, arma::uvec i, arma::uvec j)
  {
    using subv_t = arma::subview_elem2<T, arma::umat, arma::umat>;
    auto view = xptr<arma::Mat<T>>(x)->submat(i, j);
    auto subv = new subview_container<subv_t>(view);
    return Rcpp::XPtr<subview_container<subv_t>>(subv, true);
  }
};

// [[Rcpp::export]]
SEXP mat_subview(SEXP x, arma::uvec i, arma::uvec j)
{
  return dispatch_num_obj<MatSubview>(x, i - 1, j - 1);
}
