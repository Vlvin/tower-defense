#pragma once
// namespace std {
//     template<class _Tp>
//     class shared_ptr;
// }
#include <memory>

class ICloneable {
public:
  virtual std::shared_ptr<ICloneable> clone() = 0;
};