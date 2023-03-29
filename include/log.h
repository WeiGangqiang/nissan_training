#ifndef INC_35A38FE6F15B48F0B194415EFF3E56DA_H
#define INC_35A38FE6F15B48F0B194415EFF3E56DA_H

#include <stdio.h>

// If expr is not SUCCESS, print the log and return the same value
#define CHECK_FALSE_RET(expr, ...)                                             \
  do {                                                                         \
    if (!(expr)) {                                                                \
      printf(__VA_ARGS__);                                                     \
      return false;                                                            \
    }                                                                          \
  } while (false)

#endif
