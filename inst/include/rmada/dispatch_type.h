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

#ifndef INST_INCLUDE_RMADA_DISPATCH_TYPE_H_
#define INST_INCLUDE_RMADA_DISPATCH_TYPE_H_

#include <RcppArmadillo.h>

#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>

namespace mp11 = boost::mp11;

using num_types = mp11::mp_list
  <
    int,
    float,
    double
  >;

template <typename T>
using object_types = mp11::mp_list
  <
    arma::Mat<T>,
    arma::Col<T>,
    arma::Row<T>
  >;

using arma_types_grid = mp11::mp_transform<object_types, num_types>;
using arma_types_lin = mp11::mp_apply<mp11::mp_append, arma_types_grid>;

template <std::size_t DT, std::size_t AT>
using arma_type_from_ij = mp11::mp_at_c<
  mp11::mp_at_c<arma_types_grid, DT>, AT
>;

template <std::size_t I>
using arma_type_from_i = mp11::mp_at_c<arma_types_lin, I>;

template <typename T>
using i_form_arma_type = mp11::mp_find<arma_types_lin, T>;

template <std::size_t I>
using num_type_from_i = mp11::mp_at_c<num_types, I>;

template <typename T>
using i_form_num_type = mp11::mp_find<num_types, T>;

template <typename T, std::size_t N> struct dispatch_impl {
  template <std::size_t K, template<typename> class Func, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Func< mp11::mp_at_c<T, 0> >()(std::forward<Ar>(rg)...)) {
    if (i == 0) {
      return Func< mp11::mp_at_c<T, K> >()(std::forward<Ar>(rg)...);
    } else {
      return dispatch_impl<T, N - 1>::template call<K + 1, Func>(i - 1,
          std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 1> {
  template <std::size_t K, template<typename> class Func, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Func< mp11::mp_at_c<T, 0> >()(std::forward<Ar>(rg)...)) {
    if (i == 0) {
      return Func< mp11::mp_at_c<T, K> >()(std::forward<Ar>(rg)...);
    } else {
      throw std::runtime_error("number of available types exhausted.");
    }
  }
};

template <template<typename> class Func, typename ...Ar>
auto dispatch_arma_type(std::size_t type, Ar&&... rg) ->
    decltype(
      Func< mp11::mp_at_c<arma_types_lin, 0> >()(std::forward<Ar>(rg)...)
    ) {
  return dispatch_impl<
        arma_types_lin, std::size_t{mp11::mp_size<arma_types_lin>::value} 
      >::template call<0, Func>(type, std::forward<Ar>(rg)...);
}

template <template<typename> class Func, typename ...Ar>
auto dispatch_num_type(std::size_t type, Ar&&... rg) ->
    decltype(
      Func< mp11::mp_at_c<num_types, 0> >()(std::forward<Ar>(rg)...)
    ) {
  return dispatch_impl<
        num_types, std::size_t{mp11::mp_size<num_types>::value} 
      >::template call<0, Func>(type, std::forward<Ar>(rg)...);
}

template <template<typename> class Func, typename ...Ar>
auto dispatch_arma_obj(SEXP x, Ar&&... rg) ->
    decltype(
      Func< mp11::mp_at_c<arma_types_lin, 0> >()(
        std::forward<SEXP>(x), std::forward<Ar>(rg)...
      )
    ) {
  return dispatch_arma_type<Func>(Rcpp::as<std::size_t>(R_ExternalPtrTag(x)),
      std::forward<SEXP>(x), std::forward<Ar>(rg)...);
}

// idea taken from CRAN package bigstatsr

#define DISPATCH_DATA_TYPE(CALL) {                                            \
  switch (data_type) {                                                        \
    case 1: CALL(unsigned short)                                              \
    case 2: CALL(unsigned int)                                                \
    case 3: CALL(unsigned long)                                               \
    case 4: CALL(short)                                                       \
    case 5: CALL(int)                                                         \
    case 6: CALL(long)                                                        \
    case 7: CALL(float)                                                       \
    case 8: CALL(double)                                                      \
    default: throw Rcpp::exception("Unsupported data type.");                 \
  }                                                                           \
}



#endif  // INST_INCLUDE_RMADA_DISPATCH_TYPE_H_
