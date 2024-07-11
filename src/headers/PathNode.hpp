#pragma once
#include <raylib.h>
#include "Map.hpp"
#include <memory>
#include <vector>
#include "sys/types.h"

class PathNode {
public:
  PathNode(Vector2 position, uint cost);
  PathNode(MapUnit unit);
  PathNode(Vector2 position, uint cost, PathNode* prev);
  std::vector<Vector2> findPath
  (
    Map* map, 
    MapUnit goal
  );
  std::vector<Vector2> findPath
  (
    Map* map, 
    Vector2 goal
  );
  
private:
  std::vector<PathNode*> getNeighbours(Map* map);
  std::vector<Vector2> getNeighboursPositions(Map* map);
  uint manhattenDistance(Vector2 goal);
  uint getFullCost();
  void buildPath();
  bool isAlreadyPassed(uint depth);
  bool isAlreadyPassed(Vector2 position, uint depth);
  PathNode *m_prev, *m_next;
  Vector2 m_position;
  uint m_cost;
};