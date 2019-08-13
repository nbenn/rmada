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

#include <rmada/dispatch_type.h>

#include <boost/core/demangle.hpp>

struct TypeName {
  std::vector<std::string> names;
  template <typename T>
  void operator()(T)
  {
    names.push_back(boost::core::demangle(typeid(T).name()));
  }
};

// [[Rcpp::export]]
std::vector<std::string> list_num_types()
{
  return mp11::mp_for_each<num_types>(TypeName()).names;
}

// [[Rcpp::export]]
std::vector<std::string> list_mem_types()
{
  return mp11::mp_for_each<mem_types>(TypeName()).names;
}

// [[Rcpp::export]]
std::vector<std::string> list_arma_types()
{
  return mp11::mp_for_each<arma_types>(TypeName()).names;
}
