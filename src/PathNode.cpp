#include "PathNode.hpp"
#include <stdint.h>
#include "ColorTools.hpp"
#include <queue>

PathNode::PathNode(Vector2 position, uint cost)
{
  m_prev = nullptr;
  m_next = nullptr;
  m_position = position;
  m_cost = cost;
}

PathNode::PathNode(MapUnit unit)
 : PathNode(unit.position, unit.cost)
{}

PathNode::PathNode(Vector2 position, uint cost, PathNode* prev)
  : PathNode(position, cost)
{
  m_prev = prev;
}


std::vector<Vector2> PathNode::findPath
(
  Map* map, 
  MapUnit goal
) 
{
  return findPath(map, goal.position);
}

std::vector<Vector2> PathNode::findPath
(
  Map* map, 
  Vector2 goal
)
{
  Vector2 size = map->getSize();
  uint width = size.x, height = size.y;

  
  auto cmp = [&](PathNode* left, PathNode* right)
  {
    return 
    (
      ( left->manhattenDistance(goal) +  left->getFullCost()) 
    > (right->manhattenDistance(goal) + right->getFullCost())
    );
  };

  typedef struct {
    uint cost;
    PathNode* point;
  } shortcut;
  shortcut nodeMap[width*height];
  for (int i = 0; i < width*height; i++) 
    nodeMap[i] = {uint(-1), nullptr};


  std::priority_queue
  < // template
    PathNode*, 
    std::vector<PathNode*>, 
    decltype(cmp)
  > paths(cmp);


  PathNode* current = this;
  uint x = goal.x, y = goal.y;
  nodeMap[y*width+x] = {
    current->getFullCost(),
    current
  };

  paths.push(this);


  while(!CT::vec2Compare(current->m_position, goal)) 
  {

    current = paths.top();
    paths.pop();

    x = current->m_position.x, y = current->m_position.y;
    if (nodeMap[y*width+x].cost <= current->getFullCost())
    {
      if (current != nodeMap[y*width+x].point) {
        delete current;
      }
      current = nodeMap[y*width+x].point;
    }
    for (Vector2 &node : current->getNeighboursPositions(map)) {
      x = node.x, y = node.y;
      uint cellCost = current->getFullCost() + map->getUnit(x, y).cost;
      if 
      (
        (!current->isAlreadyPassed(node, 5)) && 
        (nodeMap[y*width+x].cost > cellCost)
      ) 
      {
        if (nodeMap[y*width+x].point) {
        
          delete nodeMap[y*width+x].point;
          nodeMap[y*width+x].point = nullptr;
        }
        nodeMap[y*width+x] = { 
          cellCost,
          new PathNode(node, map->getUnit(x, y).cost, current)
        };
        paths.push(nodeMap[y*width+x].point);
      }
      if (CT::vec2Compare(node, goal))
      {
        std::cout << map->getUnit(node.x, node.y).cost << '\n';
      } 
    }
  }
  printf("fuck yeah\n"); 
  // program will never reach this point
  // for some reason

  current->buildPath();
  // it will just stuck at while loop above

  std::vector<Vector2> result = {};

  while(current->m_prev) current = current->m_prev;
  while(current) {
    result.push_back(current->m_position);
    current = current->m_next;
  }
  // and will never give us result
  return result;
}

uint PathNode::manhattenDistance(Vector2 goal) {
  return 
  (
    abs(m_position.x - goal.x) +
    abs(m_position.y - goal.y)
  );
}

std::vector<PathNode*> PathNode::getNeighbours(Map* map) {
    Vector2 size = map->getSize();
    float x = m_position.x, y = m_position.y;
    std::vector<Vector2> neighbourCells = {
        {x + 1, y    },
        {x    , y + 1},
        {x - 1, y    },
        {x    , y - 1}
    };
    std::vector<PathNode*> neighbours;
    if (m_position.y <= 0) neighbourCells.pop_back();
    if (m_position.x <= 0) {
        neighbourCells[2] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (m_position.y >= (size.y - 1)) {
        neighbourCells[1] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (m_position.x >= (size.x - 1)) {
        neighbourCells[0] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    for (char i = 0; i < neighbourCells.size(); i++) {
        int x = neighbourCells[i].x, y = neighbourCells[i].y;
        neighbours.push_back
        (
          new PathNode(neighbourCells[i], (map->getUnit(x, y).cost), this)
        );
    }
    return neighbours;
}

std::vector<Vector2> PathNode::getNeighboursPositions(Map* map) {
    Vector2 size = map->getSize();
    float x = m_position.x, y = m_position.y;
    std::vector<Vector2> neighbourCells = {
        {x + 1, y    },
        {x    , y + 1},
        {x - 1, y    },
        {x    , y - 1}
    };
    if (m_position.y <= 0) neighbourCells.pop_back();
    if (m_position.x <= 0) {
        neighbourCells[2] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (m_position.y >= (size.y - 1)) {
        neighbourCells[1] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }
    if (m_position.x >= (size.x - 1)) {
        neighbourCells[0] = neighbourCells[neighbourCells.size() - 1];
        neighbourCells.pop_back();
    }

    return neighbourCells;
}

void PathNode::buildPath()
{
  /**
   * we need to set all m_next to this pointers
   * but i am using fucking shared_ptr to avoid manual deletion
  */
  if (!m_prev) return;
  PathNode* current;
  while (current->m_prev) 
  {
    current->m_prev->m_next = current;
    current = current->m_prev;
  }
}

uint PathNode::getFullCost()
{
  uint cost = m_cost;

  for (PathNode* current = m_prev; current; current = current->m_prev){
    // std::cout << current << '\n';
    cost += current->m_cost;
  }

  return cost;
}

bool PathNode::isAlreadyPassed(uint depth)
{ 
  PathNode* curr = this;
  for (uint i = 0; i < depth; i++)
  {
    if (CT::vec2Compare(curr->m_position, m_position)) return true;
    if (curr == this) return true;
  }
  curr = curr->m_prev;
  return false;
}

bool PathNode::isAlreadyPassed(Vector2 position, uint depth)
{ 
  PathNode* curr = this;
  for (uint i = 0; i < depth; i++)
  {
    if (CT::vec2Compare(curr->m_position, position)) return true;
  }
  curr = curr->m_prev;
  return false;
}