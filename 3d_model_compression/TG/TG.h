#pragma once
#include "TMesh.h"
#include "Vertex.h"
#include <Stack>

class TG {
public:
  void Encode(TMesh);
  void Decode(TMesh*);
private:
  Vertex* FindVertexOnStack(Stack, Vertex);
}
