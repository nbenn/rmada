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

#include <rmada/type_dispatch.hpp>
#include <rmada/utils.hpp>

template <typename T>
struct NRows
{
  arma::uword operator()(SEXP x)
  {
    return xptr<T>(x)->n_rows;
  }
};

// [[Rcpp::export]]
arma::uword n_rows(SEXP x)
{
  return dispatch_arma_obj<NRows>(x);
}

template <typename T>
struct NCols
{
  arma::uword operator()(SEXP x)
  {
    return xptr<T>(x)->n_cols;
  }
};

// [[Rcpp::export]]
arma::uword n_cols(SEXP x)
{
  return dispatch_arma_obj<NCols>(x);
}

template <typename T>
struct NElem
{
  arma::uword operator()(SEXP x)
  {
    return xptr<T>(x)->n_elem;
  }
};

// [[Rcpp::export]]
arma::uword n_elem(SEXP x)
{
  return dispatch_arma_obj<NElem>(x);
}

template <typename T>
struct NSlices
{
  arma::uword operator()(SEXP x)
  {
    return xptr<arma::Cube<T>>(x)->n_slices;
  }
};

// [[Rcpp::export]]
arma::uword n_slices(SEXP x)
{
  return dispatch_num_obj<NSlices>(x);
}
