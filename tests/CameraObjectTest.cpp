#include <gtest/gtest.h>
#include <Debug.h>
#include <CameraObject.hpp>
#include <Mock/InputHandler.hpp>


using ::testing::Return;

class CameraObjectTest : public ::testing::Test {
protected:
  float movementSpeed = 1.f;
  float scalingSpeed = 1.f;
  const float MIN_ZOOM = 10.f;
  const float MAX_ZOOM = 40.f;
  MockInputHandler mock_input;
  CameraObject _cameraObject{mock_input, movementSpeed, scalingSpeed };
};


TEST_F(CameraObjectTest, InitialState) {
  EXPECT_EQ(_cameraObject.getPosition().x, 2.f);
  EXPECT_EQ(_cameraObject.getPosition().y, 2.f);  
  EXPECT_EQ(_cameraObject.getScale(), 10.f); 
} 


TEST_F(CameraObjectTest, Behaviour__Movement) {
  double delta = 1.0f;
  Vector2 simulatedPosition;
  // up
  simulatedPosition = _cameraObject.getPosition(); 
  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(true));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(false));
  _cameraObject.update(delta);
  // upd position
  simulatedPosition.y -= movementSpeed * delta;
  EXPECT_FLOAT_EQ(_cameraObject.getPosition().y, simulatedPosition.y);

  // down
  simulatedPosition = _cameraObject.getPosition(); 
  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(true));
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(false));
  _cameraObject.update(delta);
  // upd position
  simulatedPosition.y += movementSpeed * delta;
  EXPECT_FLOAT_EQ(_cameraObject.getPosition().y, simulatedPosition.y);

  // left
  simulatedPosition = _cameraObject.getPosition(); 
  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(true));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(false));
  _cameraObject.update(delta);
  // upd position
  simulatedPosition.x -= movementSpeed * delta;
  EXPECT_FLOAT_EQ(_cameraObject.getPosition().y, simulatedPosition.y);

  // right
  simulatedPosition = _cameraObject.getPosition(); 
  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(true));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(false));
  _cameraObject.update(delta);
  // upd position
  simulatedPosition.x += movementSpeed * delta;
  EXPECT_FLOAT_EQ(_cameraObject.getPosition().y, simulatedPosition.y);
}


TEST_F(CameraObjectTest, Behaviour__Zoom) {
  double delta = 1.0f;
  float zoom;

 
  // zoom in
  zoom = _cameraObject.getScale();
  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(true));
  _cameraObject.update(delta);

  // upd zoom
  zoom += scalingSpeed * delta;

  EXPECT_FLOAT_EQ(_cameraObject.getScale(), zoom);



  // zoom out
  zoom = _cameraObject.getScale();

  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(true));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(false));
  _cameraObject.update(delta);

  // upd zoom
  zoom -= scalingSpeed * delta;

  EXPECT_FLOAT_EQ(_cameraObject.getScale(), zoom);

  // zoom bounds check
  delta = 100.f;

  // lower bound
  zoom = _cameraObject.getScale();

  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(true));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(false));
  _cameraObject.update(delta);

  // upd zoom
  zoom = MIN_ZOOM;

  EXPECT_FLOAT_EQ(_cameraObject.getScale(), zoom);

  // upper bound
  zoom = _cameraObject.getScale();

  EXPECT_CALL(mock_input, isKeyDown(KEY_W)).WillOnce(Return(false));    
  EXPECT_CALL(mock_input, isKeyDown(KEY_A)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_S)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_D)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_F)).WillOnce(Return(false));
  EXPECT_CALL(mock_input, isKeyDown(KEY_C)).WillOnce(Return(true));
  _cameraObject.update(delta);

  // upd zoom
  zoom = MAX_ZOOM;

  EXPECT_FLOAT_EQ(_cameraObject.getScale(), zoom);


}