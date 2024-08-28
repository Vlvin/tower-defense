#include <gtest/gtest.h>
#include <CameraObject.hpp>


class CameraObjectTest : public ::testing::Test {
protected:
  CameraObject _cameraObject{ 1.f, 5.f };
};


TEST_F(CameraObjectTest, InitialState) {
  EXPECT_EQ(_cameraObject.getPosition().x, 2.f);
  EXPECT_EQ(_cameraObject.getPosition().y, 2.f);  
  EXPECT_EQ(_cameraObject.getScale(), 10.f); 
}
