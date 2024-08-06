#pragma once


#ifdef NDEBUG
#endif

#ifdef NDEBUG
#else
#endif

#ifdef NDEBUG
  #include <iostream>
// assert
  #define DASSERT(expr) static_assert(expr);

// log  
  #define DLOG(message) std::cout << message << '\n';

// conditional log
  // if expr then DLOG(True) else DLOG(False)
  #define DLOG_IF(expr, True, False) DLOG((expr ? True : False))
#else
  #define DASSERT(expr)
  #define DLOG(message)
  #define DLOG_IF(expr, True, False)
#endif

#ifdef NDEBUG
#else
#endif