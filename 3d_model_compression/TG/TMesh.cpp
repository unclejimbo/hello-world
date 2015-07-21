#include "TMesh.h"
#include "Vertex.h"
#include <fstream>
#include <sstream>

void TMesh::ReadObj(std::string file_name) {
  std::ifstream ifs(file_name, std::ifstream::in);
  while (!ifs.eof()) {
    std::string line, first;
    std::getline(ifs, line);
    std::istringstream iss(line);
    iss >> first;
    if (first == "v") { // Read vertex
      std::string x_str, y_str, z_str;
      iss >> x_str >> y_str >> z_str;
      double x, y, z;
      x = std::stod(x_str);
      y = std::stod(y_str);
      z = std::stod(z_str);
      Vertex v(x, y, z);
      this->vertices.push_back(v);
    } else if (first == "f") { // Read triangle
      Vertex vertices[3];
      for (int i = 0; i < 3; ++i) {
        std::string temp;
        iss >> temp;
        auto split = temp.find_first_of("/");
        std::string str = temp.substr(0, split);
        int vetex = std::stoi(str);
        Vertices[i] = vertex;
      }
      Triangle triangle(vertices[0], vertices[1], vertices[2]);
      this->triangles.push_back(triangle);
    } else {
      // Blank
    }
  }
}

bool TMesh::IsTraversed() {
  return true;
}

Triangle TMesh::UnvisitedTriangle() {
  return ;
}
