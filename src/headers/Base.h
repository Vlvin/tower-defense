#include "IGameObject.h"
#include <vector>

class Base : public IGameObject {  
protected:
public:
    Base(int x, int y);
    virtual void update(float delta) override;
    // virtual void draw(float scale) override;
    virtual bool isCollidable() override;
};