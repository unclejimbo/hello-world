#pragma once
#include "../../lib/TMesh.h"
#include "ActiveList.h"
#include <Stack>
#include <iterator>

class TG {
public:
  TG() {}
  ~TG() {}
  void Encode(const TMesh&);
  void Decode(TMesh*);
private:
	std::string code;
	int *visitedTriangles;
	int *visitedVertices;
	int *visitedTimes;
	bool *alreadyErased;
  ActiveList *FindOnStack(std::stack<ActiveList*> stack, int index);
	int FindUnvisitedTriangle(const TMesh &mesh);
};

// Return the pointer to the AL contains the split index on stack
ActiveList* TG::FindOnStack(std::stack<ActiveList*> stack, int index)
{
	std::stack<ActiveList*> container;
	while (!stack.empty()) {
		ActiveList *p = stack.top();
		if (p->Contains(index)) {
			stack.pop();
			return p;
		}
		container.push(p);
		stack.pop();
	}
	while (!container.empty()) {
		stack.push(container.top());
		container.pop();
	}
}

// Return the index to an unvisited tirangle
// Return 0 if all triangles are visited
int TG::FindUnvisitedTriangle(const TMesh &mesh) {
	int i = 1;
	while (visitedTriangles[i++] != 0) {
		if (i > mesh.triangles.size())
			return 0;
	}
	visitedTriangles[i - 1] = 1;
	return i - 1;
}

void TG::Encode(const TMesh &mesh) {
	std::stack<ActiveList*> imcomplete_lists;
	ActiveList AL, AL1;
	visitedTriangles = new int[mesh.triangles.size() + 1];
	for (int i = 0; i < mesh.triangles.size() + 1; ++i)
		visitedTriangles[i] = 0;
	visitedVertices = new int[mesh.vertices.size() + 1];
	visitedTimes = new int[mesh.vertices.size() + 1];
	alreadyErased = new bool[mesh.vertices.size() + 1];
	for (int i = 0; i < mesh.vertices.size() + 1; ++i) {
		visitedVertices[i] = 0;
		visitedTimes[i] = mesh.degrees[i];
		alreadyErased[i] = false;
	}

	while (int i = FindUnvisitedTriangle(mesh)) {
		--i;
		tri triangle = mesh.triangles[i];
		AL.Add({ triangle.index1, triangle.index2, triangle.index3 });
		std::string str_int = std::to_string(mesh.degrees[triangle.index1]);
		code += " add " + str_int;
		str_int = std::to_string(mesh.degrees[triangle.index2]);
		code += " add " + str_int;
		str_int = std::to_string(mesh.degrees[triangle.index3]);
		code += " add " + str_int;
		AL.focus = triangle.index1;
		imcomplete_lists.push(&AL);

		while (!imcomplete_lists.empty()) {
			AL = *imcomplete_lists.top();
			imcomplete_lists.pop();

			TMesh::Node *neighbor = mesh.neighbors[AL.focus];
			while (!AL.Empty()) {
				neighbor = neighbor->next;
				if (!neighbor)
					break;
				if (visitedVertices[neighbor->index] == 0) { // Unvisited
					AL.Add({ neighbor->index });
					std::string neighbor_str = std::to_string(mesh.degrees[neighbor->index]);
					code += " add " + neighbor_str;
					visitedVertices[neighbor->index] = 1;
					--visitedTimes[AL.focus];
					--visitedTimes[neighbor->index];
				}
				else {
					if (AL.Contains(neighbor->index)) { // In current AL
						int offset = AL.Split(&AL1, neighbor->index);
						std::string offset_str = std::to_string(offset);
						imcomplete_lists.push(&AL1);
						code += " split " + offset_str;
					}
					else { // In some AL on stack
						ActiveList *al = FindOnStack(imcomplete_lists, neighbor->index);
						AL.Merge(al, neighbor->index);
						// Do nothing
						// Do something when treating torus-like meshes
					}
				}
				// Remove full vertices
				for (int i = 0; i < mesh.vertices.size(); ++i) {
					i = i + 1;
					if (!alreadyErased[i] && visitedTimes[i] == 0) {
						AL.active_indices.erase(std::find(
							AL.active_indices.begin(), AL.active_indices.end(), i));
						alreadyErased[i] = true;
					}
				}
				if (visitedTimes[AL.focus] == 0)
					AL.focus = AL.active_indices[0];
			}
		}
	}
}

void TG::Decode(TMesh *mesh) {
	ActiveList AL, AL1;
	std::stack<ActiveList*> S;
	std::stringstream ss(code);

	// Build topological info
	while (!ss.eof()) {
		// Build the initial triangle
		int index1, index2, index3;
		std::string cmd;
		ss >> cmd >> index1;  // cmd is sure to be "add"
		ss >> cmd >> index2;
		ss >> cmd >> index3;
		tri init = { index1, index2, index3 };
		mesh->triangles.push_back(init);
		AL.Add({ index1, index2, index3 });
		AL.focus = index1;
		S.push(&AL);

		while (!S.empty()) {
			AL = *S.top();
			S.pop();
			while (!AL.Empty()) {
				ss >> cmd;
				// TODO
				// 
				//
				if (cmd == "add") {
					int index;
					ss >> index;
				}
				else if (cmd == "split") {
					int index;
					ss >> index;
				}
				else if (cmd == "merge") {
					int index1, index2;
					ss >> index1 >> index2;
				}
			}
		}
	}
}