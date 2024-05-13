#include "IGameObject.h"
#include <vector>

class Base : public IGameObject {  
    static std::vector<Base*> all;
protected:
public:
    Base(int x, int y);
    virtual void update(float delta);
    virtual void draw(float scale);
};