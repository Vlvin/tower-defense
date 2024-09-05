#include <gmock/gmock.h>


class ClickPlaceHolder {
public:
  MOCK_CONST_METHOD0(onClick, void());
};