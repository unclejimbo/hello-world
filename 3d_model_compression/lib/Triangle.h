#pragma once
#include "Vertex.h"

class Triangle {
public:
  Triangle() {}
  ~Triangle() {}
Triangle(int v1, int v2, int v3) :
  v_index1(v1), v_index2(v2), v_index3(v3) {}

  int v_index1, v_index2, v_index3;
}
