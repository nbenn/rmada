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

#include <RcppArmadillo.h>

template <typename T>
SEXP mat_init(Rcpp::XPtr<Memory> mem, arma::uword n_rows, arma::uword n_cols) {
  T* ptr = static_cast<T*>(mem->get_address());
  arma::Mat<T>* res = new arma::Mat<T>(ptr, n_rows, n_cols, false, true);
  return Rcpp::XPtr< arma::Mat<T> >(res);
}

#define MAT_INIT(TYPE) return mat_init<TYPE>(mem, n_rows, n_cols);

// [[Rcpp::export]]
SEXP mat_init(Rcpp::XPtr<Memory> mem, arma::uword n_rows, arma::uword n_cols,
    int data_type) {
  DISPATCH_DATA_TYPE(MAT_INIT)
}

template <typename T>
arma::uword mat_n_rows(SEXP mat) {
  Rcpp::XPtr< arma::Mat<T> > p(mat);
  return p->n_rows;
}

#define MAT_N_ROWS(TYPE) return mat_n_rows<TYPE>(mat);

// [[Rcpp::export]]
arma::uword mat_n_rows(SEXP mat, int data_type) {
  DISPATCH_DATA_TYPE(MAT_N_ROWS)
}

template <typename T>
arma::uword mat_n_cols(SEXP mat) {
  Rcpp::XPtr< arma::Mat<T> > p(mat);
  return p->n_cols;
}

#define MAT_N_COLS(TYPE) return mat_n_cols<TYPE>(mat);

// [[Rcpp::export]]
arma::uword mat_n_cols(SEXP mat, int data_type) {
  DISPATCH_DATA_TYPE(MAT_N_COLS)
}
