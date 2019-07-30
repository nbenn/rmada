#ifndef TYPES_H
#define TYPES_H

#include "mem.h"

// idea taken from CRAN package bigstatsr

#define DISPATCH_DATA_TYPE(CALL) {                                            \
  switch(data_type) {                                                         \
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

#endif // TYPES_H
