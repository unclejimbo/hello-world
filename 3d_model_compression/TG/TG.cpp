#include "TG.h"
#include "ActiveList.h"
#include <Stack>
#include <iostream>

void TG::Encode(TMesh m) {
  std::Stack<ActiveList> S;
  ActiveList AL, AL1;

  while(!M.isTraversed()) {
    Triangle tri = M.unvisitedTriangle();
    AL.Add(tri.v1, tri.v2, tri.v3);
    AL.focus = tri.v1;
    S.push(AL);

    while (!S.empty()) {
      ActiveList AL = S.pop();
      while (!AL.empty()) {
        Edge edge = AL.focus.FreeEdge();
        Vertex neighbor = AL.focus.Neighbor(edge);
        if (neghbor.IsFree()) {
          AL.Add(neighbor);
          std::cout << "add " << neighbor.degree << std::endl;
        } else {
          if (AL.Contains(neighbor)) {
            AL.Split(AL, AL1);
            S.push(AL1);
            std::cout << "split" << AL.Offset(neighbor) << std::endl;
          } else {
            Vertex *vp = FindVertexOnStack(S, neighbor);
            S.pop(AL1);
            AL.Merge(AL1, neighbor);
          }
          AL.RemoveFullVertices();
          if (AL.focus.IsFull())
            AL.focus = AL.focus.NextNeighbor();
        }
      }
    }
  }
}
