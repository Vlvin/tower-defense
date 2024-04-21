#pragma once
#include "IGameObject.h"
#include <memory>
#include <vector>

class Bullet : public IGameObject {
private:
    static std::vector<std::shared_ptr<Bullet>> all;
protected:
    
    float speed, radius;
public:
    Bullet(Vector2 position, float radius, float speed, float angle);
    virtual void update(float delta) override;
    virtual void draw(float scale) override;
    float getSpeed();
    static void cleanUp();
    static long count();
    static std::shared_ptr<Bullet> get(long index);
    static void updateAll(float delta);
    static void drawAll(float scale);
};