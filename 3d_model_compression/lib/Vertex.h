#pragma once

class Vertex {
public:
  Vertex() {}
  ~Vertex() {}
Vertex(double vx, double vy, double vz) :
  x(vx), y(vy), z(vz) {}

  double x, y, z;
  int degree;
  int neighbors[];
}
