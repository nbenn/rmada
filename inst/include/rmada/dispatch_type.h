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
