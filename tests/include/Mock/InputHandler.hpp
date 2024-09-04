#pragma once
#include <InputHandler.hpp>
#include <raylib.h>
#include <gmock/gmock.h>

class MockInputHandler : public InputHandler
{
public:
  MOCK_CONST_METHOD1(isKeyDown, bool(int key));
  MOCK_CONST_METHOD1(isMouseButtonPressed, bool(int key));
  MOCK_CONST_METHOD0(getMousePosition, Vector2());
};