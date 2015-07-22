#pragma once
#include <string>
#include <vector>

// Data type definition
typedef double vec[3];
typedef double tri[3];

class TMesh {
public:
  TMesh() {}
  ~TMesh() {}
  bool IsTraversed(); // Is every triangle visited?
  Triangle UnvisitedTriangle(); // Return an unvisited triangle
  void ReadObj(std::string file_name);
private:
  std::vector<vec> vertices;
  std::vector<tri> triangles;
  void BuildTopo();
}
