#include <GameObjects/Button.hpp>
#include <CameraObject.hpp>
#include <Mock/InputHandler.hpp>
#include <Mock/ClickPlaceHolder.hpp>
#include <gtest/gtest.h>

using ::testing::Return;

class ButtonTest : public ::testing::Test {
protected:
  MockInputHandler mock_input;
  ClickPlaceHolder ph;
  Rectangle _body{1.f, 1.f, 10.f, 10.f};
  Color _color = WHITE;
  CameraObject _camera{mock_input, 1.f, 1.f};
  Button _btn = Button(Button(mock_input, _body, [this] {this->ph.onClick();}), _color);
};

TEST_F(ButtonTest, InitialState) {
  Rectangle actual_body = _btn.getBody();
  Color actual_color = _btn.getColor();
  
  EXPECT_FLOAT_EQ(actual_body.x, _body.x);
  EXPECT_FLOAT_EQ(actual_body.y, _body.y);
  EXPECT_FLOAT_EQ(actual_body.width, _body.width);
  EXPECT_FLOAT_EQ(actual_body.height, _body.height);
  
  EXPECT_FLOAT_EQ(actual_color.r, _color.r);
  EXPECT_FLOAT_EQ(actual_color.g, _color.g);
  EXPECT_FLOAT_EQ(actual_color.b, _color.b);
  EXPECT_FLOAT_EQ(actual_color.a, _color.a);
}

TEST_F(ButtonTest, Behaviour) {
  float delta = 1.f;
  Vector2 onButton{_body.x+1, _body.y+1};
  Vector2 outOfButton{_body.x-1, _body.y-1};
  Vector2 onButtonBorder{_body.x, _body.y};
  // color change on covering
  EXPECT_CALL(mock_input, getMousePosition()).WillOnce(Return(onButton));
  EXPECT_CALL(mock_input, isMouseButtonPressed(MOUSE_BUTTON_LEFT)).WillOnce(Return(false));
  _btn.update(delta, _camera);
  Color normal_covering_color = _btn.getColor();

  EXPECT_FLOAT_EQ(normal_covering_color.r, _color.r-20);
  EXPECT_FLOAT_EQ(normal_covering_color.g, _color.g-20);
  EXPECT_FLOAT_EQ(normal_covering_color.b, _color.b-20);
  EXPECT_FLOAT_EQ(normal_covering_color.a, _color.a-20);
  
  // click
  EXPECT_CALL(mock_input, getMousePosition()).WillOnce(Return(onButton));
  EXPECT_CALL(mock_input, isMouseButtonPressed(MOUSE_BUTTON_LEFT)).WillOnce(Return(true));
  EXPECT_CALL(ph, onClick);
  _btn.update(delta, _camera);
  Color normal_click_color = _btn.getColor();

  EXPECT_FLOAT_EQ(normal_click_color.r, _color.r-40);
  EXPECT_FLOAT_EQ(normal_click_color.g, _color.g-40);
  EXPECT_FLOAT_EQ(normal_click_color.b, _color.b-40);
  EXPECT_FLOAT_EQ(normal_click_color.a, _color.a-40);

  _btn.setColor(BLACK);
  _color = BLACK;

  EXPECT_CALL(mock_input, getMousePosition()).WillOnce(Return(outOfButton));
  _btn.update(delta, _camera);

  Color actual_color = _btn.getColor();
  EXPECT_EQ(actual_color.r, _color.r);
  EXPECT_EQ(actual_color.g, _color.g);
  EXPECT_EQ(actual_color.b, _color.b);

  // overflow color change on covering
  EXPECT_CALL(mock_input, getMousePosition()).WillOnce(Return(onButton));
  EXPECT_CALL(mock_input, isMouseButtonPressed(MOUSE_BUTTON_LEFT)).WillOnce(Return(false));
  _btn.update(delta, _camera);
  Color overflow_covering_color = _btn.getColor();

  EXPECT_EQ(overflow_covering_color.r, _color.r);
  EXPECT_EQ(overflow_covering_color.g, _color.g);
  EXPECT_EQ(overflow_covering_color.b, _color.b);
  EXPECT_EQ(overflow_covering_color.a, _color.a-20);
  
  // overflow click
  EXPECT_CALL(mock_input, getMousePosition()).WillOnce(Return(onButton));
  EXPECT_CALL(mock_input, isMouseButtonPressed(MOUSE_BUTTON_LEFT)).WillOnce(Return(true));
  EXPECT_CALL(ph, onClick);
  _btn.update(delta, _camera);
  Color overflow_click_color = _btn.getColor();

  EXPECT_EQ(overflow_click_color.r, _color.r);
  EXPECT_EQ(overflow_click_color.g, _color.g);
  EXPECT_EQ(overflow_click_color.b, _color.b);
  EXPECT_EQ(overflow_click_color.a, _color.a-40);
  
  // border click
  EXPECT_CALL(mock_input, getMousePosition()).WillOnce(Return(onButtonBorder));
  EXPECT_CALL(mock_input, isMouseButtonPressed(MOUSE_BUTTON_LEFT)).Times(0);
  EXPECT_CALL(ph, onClick).Times(0);
  _btn.update(delta, _camera);
}