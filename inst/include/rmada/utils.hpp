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

#ifndef INST_INCLUDE_RMADA_UTILS_H_
#define INST_INCLUDE_RMADA_UTILS_H_

#include <RcppArmadillo.h>

template <typename T>
Rcpp::XPtr<T> xptr(SEXP x)
{
  return Rcpp::XPtr<T>(x, R_ExternalPtrTag(x), R_ExternalPtrProtected(x));
}

Rcpp::IntegerVector create_tag(std::size_t = NA_INTEGER,
    std::size_t = NA_INTEGER, std::size_t = NA_INTEGER);
std::size_t get_tag_val(SEXP, std::string);

#endif  // INST_INCLUDE_RMADA_UTILS_H_
