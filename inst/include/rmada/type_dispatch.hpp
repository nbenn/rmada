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

#ifndef INST_INCLUDE_RMADA_TYPE_DISPATCH_H_
#define INST_INCLUDE_RMADA_TYPE_DISPATCH_H_

#include <rmada/type_lists.hpp>
#include <rmada/utils.hpp>

#if defined( _MSC_VER ) && !defined( __clang__ )
# define MP11_UNREACHABLE() __assume(false)
#else
# define MP11_UNREACHABLE() __builtin_unreachable()
#endif

template <typename T, std::size_t N> struct dispatch_impl
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
      case 11: return Fn<mp11::mp_at_c<T, K + 11>>()(std::forward<Ar>(rg)...);
      case 12: return Fn<mp11::mp_at_c<T, K + 12>>()(std::forward<Ar>(rg)...);
      case 13: return Fn<mp11::mp_at_c<T, K + 13>>()(std::forward<Ar>(rg)...);
      case 14: return Fn<mp11::mp_at_c<T, K + 14>>()(std::forward<Ar>(rg)...);
      case 15: return Fn<mp11::mp_at_c<T, K + 15>>()(std::forward<Ar>(rg)...);
    }

    return dispatch_impl<T, N - 16>::template call<K + 16, Fn>(
        i - 16, std::forward<Ar>(rg)...);
  }
};

template <typename T> struct dispatch_impl<T, 0> { };

template <typename T> struct dispatch_impl<T, 1>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    return Fn<mp11::mp_at_c<T, K>>()(std::forward<Ar>(rg)...);
  }
};

template <typename T> struct dispatch_impl<T, 2>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 3>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 4>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 5>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
      case 4: return Fn<mp11::mp_at_c<T, K + 4>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 6>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
      case 4: return Fn<mp11::mp_at_c<T, K + 4>>()(std::forward<Ar>(rg)...);
      case 5: return Fn<mp11::mp_at_c<T, K + 5>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 7>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
      case 4: return Fn<mp11::mp_at_c<T, K + 4>>()(std::forward<Ar>(rg)...);
      case 5: return Fn<mp11::mp_at_c<T, K + 5>>()(std::forward<Ar>(rg)...);
      case 6: return Fn<mp11::mp_at_c<T, K + 6>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 8>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
      case 4: return Fn<mp11::mp_at_c<T, K + 4>>()(std::forward<Ar>(rg)...);
      case 5: return Fn<mp11::mp_at_c<T, K + 5>>()(std::forward<Ar>(rg)...);
      case 6: return Fn<mp11::mp_at_c<T, K + 6>>()(std::forward<Ar>(rg)...);
      case 7: return Fn<mp11::mp_at_c<T, K + 7>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 9>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
      case 4: return Fn<mp11::mp_at_c<T, K + 4>>()(std::forward<Ar>(rg)...);
      case 5: return Fn<mp11::mp_at_c<T, K + 5>>()(std::forward<Ar>(rg)...);
      case 6: return Fn<mp11::mp_at_c<T, K + 6>>()(std::forward<Ar>(rg)...);
      case 7: return Fn<mp11::mp_at_c<T, K + 7>>()(std::forward<Ar>(rg)...);
      case 8: return Fn<mp11::mp_at_c<T, K + 8>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 10>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case 0: return Fn<mp11::mp_at_c<T, K + 0>>()(std::forward<Ar>(rg)...);
      case 1: return Fn<mp11::mp_at_c<T, K + 1>>()(std::forward<Ar>(rg)...);
      case 2: return Fn<mp11::mp_at_c<T, K + 2>>()(std::forward<Ar>(rg)...);
      case 3: return Fn<mp11::mp_at_c<T, K + 3>>()(std::forward<Ar>(rg)...);
      case 4: return Fn<mp11::mp_at_c<T, K + 4>>()(std::forward<Ar>(rg)...);
      case 5: return Fn<mp11::mp_at_c<T, K + 5>>()(std::forward<Ar>(rg)...);
      case 6: return Fn<mp11::mp_at_c<T, K + 6>>()(std::forward<Ar>(rg)...);
      case 7: return Fn<mp11::mp_at_c<T, K + 7>>()(std::forward<Ar>(rg)...);
      case 8: return Fn<mp11::mp_at_c<T, K + 8>>()(std::forward<Ar>(rg)...);
      case 9: return Fn<mp11::mp_at_c<T, K + 9>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 11>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 12>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
      case 11: return Fn<mp11::mp_at_c<T, K + 11>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 13>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
      case 11: return Fn<mp11::mp_at_c<T, K + 11>>()(std::forward<Ar>(rg)...);
      case 12: return Fn<mp11::mp_at_c<T, K + 12>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 14>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
      case 11: return Fn<mp11::mp_at_c<T, K + 11>>()(std::forward<Ar>(rg)...);
      case 12: return Fn<mp11::mp_at_c<T, K + 12>>()(std::forward<Ar>(rg)...);
      case 13: return Fn<mp11::mp_at_c<T, K + 13>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 15>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
      case 11: return Fn<mp11::mp_at_c<T, K + 11>>()(std::forward<Ar>(rg)...);
      case 12: return Fn<mp11::mp_at_c<T, K + 12>>()(std::forward<Ar>(rg)...);
      case 13: return Fn<mp11::mp_at_c<T, K + 13>>()(std::forward<Ar>(rg)...);
      case 14: return Fn<mp11::mp_at_c<T, K + 14>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename T> struct dispatch_impl<T, 16>
{
  template <std::size_t K, template<typename> class Fn, typename ...Ar>
  static auto call(std::size_t i, Ar&&... rg) ->
      decltype(Fn<mp11::mp_at_c<T, 0>>()(std::forward<Ar>(rg)...))
  {
    switch(i)
    {
      default: MP11_UNREACHABLE();
      case  0: return Fn<mp11::mp_at_c<T, K +  0>>()(std::forward<Ar>(rg)...);
      case  1: return Fn<mp11::mp_at_c<T, K +  1>>()(std::forward<Ar>(rg)...);
      case  2: return Fn<mp11::mp_at_c<T, K +  2>>()(std::forward<Ar>(rg)...);
      case  3: return Fn<mp11::mp_at_c<T, K +  3>>()(std::forward<Ar>(rg)...);
      case  4: return Fn<mp11::mp_at_c<T, K +  4>>()(std::forward<Ar>(rg)...);
      case  5: return Fn<mp11::mp_at_c<T, K +  5>>()(std::forward<Ar>(rg)...);
      case  6: return Fn<mp11::mp_at_c<T, K +  6>>()(std::forward<Ar>(rg)...);
      case  7: return Fn<mp11::mp_at_c<T, K +  7>>()(std::forward<Ar>(rg)...);
      case  8: return Fn<mp11::mp_at_c<T, K +  8>>()(std::forward<Ar>(rg)...);
      case  9: return Fn<mp11::mp_at_c<T, K +  9>>()(std::forward<Ar>(rg)...);
      case 10: return Fn<mp11::mp_at_c<T, K + 10>>()(std::forward<Ar>(rg)...);
      case 11: return Fn<mp11::mp_at_c<T, K + 11>>()(std::forward<Ar>(rg)...);
      case 12: return Fn<mp11::mp_at_c<T, K + 12>>()(std::forward<Ar>(rg)...);
      case 13: return Fn<mp11::mp_at_c<T, K + 13>>()(std::forward<Ar>(rg)...);
      case 14: return Fn<mp11::mp_at_c<T, K + 14>>()(std::forward<Ar>(rg)...);
      case 15: return Fn<mp11::mp_at_c<T, K + 15>>()(std::forward<Ar>(rg)...);
    }
  }
};

template <typename L, template<typename> class Fn, typename ...Ar>
auto dispatch_type(std::size_t i, Ar&&... rg) ->
    decltype(Fn<mp11::mp_at_c<L, 0>>()(std::forward<Ar>(rg)...))
{
  using max = mp11::mp_size<L>;
  if (i >= std::size_t{max::value})
  {
    throw std::runtime_error("Index exceeds type list length.");
  }
  using disp = dispatch_impl<L, std::size_t{max::value}>;
  return disp::template call<0, Fn>(i, std::forward<Ar>(rg)...);
}

template <template<typename> class Fn, typename ...Ar>
auto dispatch_num_type(std::size_t type, Ar&&... rg) ->
    decltype(Fn<num_type_from_i<0>>()(std::forward<Ar>(rg)...))
{
  return dispatch_type<num_types, Fn>(type, std::forward<Ar>(rg)...);
}

template <template<typename> class Fn, typename ...Ar>
auto dispatch_num_obj(SEXP x, Ar&&... rg) ->
    decltype(Fn<num_type_from_i<0>>()(
      std::forward<SEXP>(x), std::forward<Ar>(rg)...
    ))
{
  auto type = get_tag_val(x, "num_type");
  return dispatch_num_type<Fn>(type, std::forward<SEXP>(x),
      std::forward<Ar>(rg)...);
}

template <template<typename> class Fn, typename ...Ar>
auto dispatch_mem(SEXP x, Ar&&... rg) ->
    decltype(Fn<num_type_from_i<0>>()(
      std::forward<SEXP>(x), std::forward<Ar>(rg)...
    ))
{
  auto type = get_tag_val(x, "num_type");
  return dispatch_num_type<Fn>(type, std::forward<SEXP>(x),
      std::forward<Ar>(rg)...);
}

template <template<typename> class Fn, typename ...Ar>
auto dispatch_arma_type(std::size_t type, Ar&&... rg) ->
    decltype(Fn<arma_type_from_i<0>>()(std::forward<Ar>(rg)...))
{
  return dispatch_type<arma_types, Fn>(type, std::forward<Ar>(rg)...);
}

template <template<typename> class Fn, typename ...Ar>
auto dispatch_arma_obj(SEXP x, Ar&&... rg) ->
    decltype(Fn<arma_type_from_i<0>>()(
      std::forward<SEXP>(x), std::forward<Ar>(rg)...
    ))
{
  auto type = get_tag_val(x, "arma_type");
  return dispatch_arma_type<Fn>(type, std::forward<SEXP>(x),
      std::forward<Ar>(rg)...);
}

#endif  // INST_INCLUDE_RMADA_TYPE_DISPATCH_H_
