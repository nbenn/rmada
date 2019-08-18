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

#ifndef INST_INCLUDE_RMADA_TYPE_LISTS_H_
#define INST_INCLUDE_RMADA_TYPE_LISTS_H_

#include <rmada/mem.hpp>

#include <RcppArmadillo.h>

#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>

namespace mp11 = boost::mp11;

using mem_types = mp11::mp_list<
  SharedMemory,
  FileMemory
>;

using num_types = mp11::mp_list<
  unsigned short,
  unsigned int,
  unsigned long,
  short,
  int,
  long,
  float,
  double
>;

template <typename T>
using object_types = mp11::mp_list<
  arma::Mat<T>,
  arma::Col<T>,
  arma::Row<T>,
  arma::Cube<T>
>;

using arma_types = mp11::mp_apply<
  mp11::mp_append, mp11::mp_transform<object_types, num_types>
>;

template <std::size_t DT, std::size_t AT>
using arma_type_from_ij = mp11::mp_at_c<
  mp11::mp_at_c<mp11::mp_transform<object_types, num_types>, DT>, AT
>;

template <std::size_t I>
using arma_type_from_i = mp11::mp_at_c<arma_types, I>;

template <typename T>
using i_form_arma_type = mp11::mp_find<arma_types, T>;

template <std::size_t I>
using num_type_from_i = mp11::mp_at_c<num_types, I>;

template <typename T>
using i_form_num_type = mp11::mp_find<num_types, T>;

template <std::size_t I>
using mem_type_from_i = mp11::mp_at_c<mem_types, I>;

template <typename T>
using i_form_mem_type = mp11::mp_find<mem_types, T>;

template <typename T>
using num_i_from_nested = mp11::mp_find<
  num_types, mp11::mp_front<mp11::mp_rename<T, mp11::mp_list>>
>;

template <typename T>
using num_type_from_nested = mp11::mp_at<num_types, num_i_from_nested<T>>;

#endif  // INST_INCLUDE_RMADA_TYPE_LISTS_H_
