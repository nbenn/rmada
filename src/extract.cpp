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

template <typename T>
struct MatExtractElem
{
  SEXP operator()(SEXP x, arma::uword i, arma::uword j)
  {
    T res = xptr<arma::Mat<T>>(x)->operator()(i, j);
    return Rcpp::wrap(res);
  }
};

// [[Rcpp::export]]
SEXP mat_extract_elem(SEXP x, arma::uword i, arma::uword j)
{
  return dispatch_num_obj<MatExtractElem>(x, i - 1, j - 1);
}

template <typename T>
struct MatExtractCol
{
  SEXP operator()(SEXP x, arma::uword j)
  {
    return Rcpp::wrap(xptr<arma::Mat<T>>(x)->col(j));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_col(SEXP x, arma::uword j)
{
  return dispatch_num_obj<MatExtractCol>(x, j - 1);
}

template <typename T>
struct MatExtractSubCol
{
  SEXP operator()(SEXP x, arma::uword j, arma::uword fist_row,
      arma::uword last_row)
  {
    return Rcpp::wrap(
        xptr<arma::Mat<T>>(x)->operator()(arma::span(fist_row, last_row), j));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_subcol(SEXP x, arma::uword j, arma::uword fist_row,
    arma::uword last_row)
{
  return dispatch_num_obj<MatExtractSubCol>(x, j - 1, fist_row - 1,
      last_row - 1);
}

template <typename T>
struct MatExtractRow
{
  SEXP operator()(SEXP x, arma::uword i)
  {
    return Rcpp::wrap(xptr<arma::Mat<T>>(x)->row(i));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_row(SEXP x, arma::uword i)
{
  return dispatch_num_obj<MatExtractRow>(x, i - 1);
}

template <typename T>
struct MatExtractSubRow
{
  SEXP operator()(SEXP x, arma::uword i, arma::uword first_col,
      arma::uword last_col)
  {
    return Rcpp::wrap(
      xptr<arma::Mat<T>>(x)->operator()(i, arma::span(first_col, last_col)));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_subrow(SEXP x, arma::uword i, arma::uword first_col,
    arma::uword last_col)
{
  return dispatch_num_obj<MatExtractSubRow>(x, i - 1, first_col - 1,
      last_col - 1);
}

template <typename T>
struct MatExtractCols
{
  SEXP operator()(SEXP x, arma::uword first, arma::uword last)
  {
    return Rcpp::wrap(xptr<arma::Mat<T>>(x)->cols(first, last));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_cols(SEXP x, arma::uword first, arma::uword last)
{
  return dispatch_num_obj<MatExtractCols>(x, first - 1, last - 1);
}

template <typename T>
struct MatExtractNcCols
{
  SEXP operator()(SEXP x, arma::uvec j)
  {
    arma::Mat<T> res = xptr<arma::Mat<T>>(x)->cols(j);
    return Rcpp::wrap(res);
  }
};

// [[Rcpp::export]]
SEXP mat_extract_nccols(SEXP x, arma::uvec j)
{
  return dispatch_num_obj<MatExtractNcCols>(x, j - 1);
}

template <typename T>
struct MatExtractRows
{
  SEXP operator()(SEXP x, arma::uword first, arma::uword last)
  {
    return Rcpp::wrap(xptr<arma::Mat<T>>(x)->rows(first, last));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_rows(SEXP x, arma::uword first, arma::uword last)
{
  return dispatch_num_obj<MatExtractRows>(x, first - 1, last - 1);
}

template <typename T>
struct MatExtractNcRows
{
  SEXP operator()(SEXP x, arma::uvec i)
  {
    arma::Mat<T> res = xptr<arma::Mat<T>>(x)->rows(i);
    return Rcpp::wrap(res);
  }
};

// [[Rcpp::export]]
SEXP mat_extract_ncrows(SEXP x, arma::uvec i)
{
  return dispatch_num_obj<MatExtractNcRows>(x, i - 1);
}

template <typename T>
struct MatExtractSubmat
{
  SEXP operator()(SEXP x, arma::uword i, arma::uword j, arma::uword last_row,
      arma::uword last_col)
  {
    return Rcpp::wrap(xptr<arma::Mat<T>>(x)->submat(i, j, last_row, last_col));
  }
};

// [[Rcpp::export]]
SEXP mat_extract_submat(SEXP x, arma::uword i, arma::uword j,
    arma::uword last_row, arma::uword last_col)
{
  return dispatch_num_obj<MatExtractSubmat>(x, i - 1, j - 1, last_row - 1,
      last_col - 1);
}

template <typename T>
struct MatExtractNcSubmat
{
  SEXP operator()(SEXP x, arma::uvec i, arma::uvec j)
  {
    arma::Mat<T> res = xptr<arma::Mat<T>>(x)->submat(i, j);
    return Rcpp::wrap(res);
  }
};

// [[Rcpp::export]]
SEXP mat_extract_ncsubmat(SEXP x, arma::uvec i, arma::uvec j)
{
  return dispatch_num_obj<MatExtractNcSubmat>(x, i - 1, j - 1);
}
