#pragma once

// assert
#ifdef NDEBUG
  #define DASSERT(expr) static_assert(expr);
#else
  #define DASSERT(expr)
#endif

// log
#ifdef NDEBUG
  #include <iostream>
  #define DLOG(expr) std::cout << expr << '\n';
#else
  #define DLOG(expr)
#endif