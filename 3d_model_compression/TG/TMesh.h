#pragma once
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <vector>

class TMesh {
public:
  TMesh() {}
  ~TMesh() {}
  bool IsTraversed(); // Is every triangle visited?
  Triangle UnvisitedTriangle(); // Return an unvisited triangle
  void ReadObj(std::string file_name);
private:
  std::vector<Vertex> vertices;
  std::vector<Triangle> triangles;
}
