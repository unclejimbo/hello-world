#pragma once
#include "TMesh.h"
#include "Vertex.h"
#include <Stack>

class TG {
public:
  TG() {}
  ~TG() {}
  void Encode(TMesh);
  void Decode(TMesh*);
private:
  Vertex* FindVertexOnStack(Stack, Vertex);
}
