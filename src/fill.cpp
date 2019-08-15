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
struct FillPredefined
{
  void operator()(SEXP x, std::size_t how)
  {
    switch(how)
    {
      case 0: xptr<T>(x)->zeros(); break;
      case 1: xptr<T>(x)->ones(); break;
      case 3: xptr<T>(x)->randu(); break;
      case 4: xptr<T>(x)->randn(); break;
      default: throw std::runtime_error("Unsupported fill type.");
    }
  }
};

template <typename T>
struct FillEye
{
  void operator()(SEXP x)
  {
    xptr<arma::Mat<T>>(x)->eye();
  }
};

// [[Rcpp::export]]
void fill_predefined(SEXP x, std::size_t how)
{
  if (how == 2)
  {
    dispatch_num_obj<FillEye>(x);
  }
  else
  {
    dispatch_arma_obj<FillPredefined>(x, how);    
  }
}

template <typename T>
struct FillValue
{
  void operator()(SEXP x, SEXP what)
  {
    auto val = Rcpp::as<num_type_from_nested<T>>(what);
    xptr<T>(x)->fill(val);
  }
};

// [[Rcpp::export]]
void fill_value(SEXP x, SEXP what)
{
  dispatch_arma_obj<FillValue>(x, what);
}
