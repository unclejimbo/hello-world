#pragma once
#include "../../src/TMesh/TMesh.h"
#include "ActiveList.h"
#include <Stack>
#include <iterator>

class TG {
public:
  TG(TMesh &mesh_in) {
		mesh = &mesh_in;
	}
  ~TG() {
		delete[] visitedTriangles;
		delete[] visitedVertices;
		delete[] visitedTimes;
		delete[] indices;
		delete[] alreadyErased;
	}
  void Encode();
  void Decode(TMesh*);
private:
	std::string code;
	int *visitedTriangles;
	int *visitedVertices;
	int *visitedTimes;
	int *indices;  // Indices of the topo traversal
	bool *alreadyErased;
	TMesh* mesh;
  ActiveList *FindOnStack(std::stack<ActiveList*> stack, int index);
	int FindUnvisitedTriangle();
	void Add(ActiveList* AL, int index);
	void Split(ActiveList* AL, ActiveList* AL1, int index, std::stack<ActiveList*> S);
};

// Add cmd
void TG::Add(ActiveList* AL, int index) {
	AL->Add(index);
	static int index_count = 1;
	indices[index_count++] = index;
	std::string str_index = std::to_string(index);
	code += "add" + str_index;
	visitedVertices[index] = 1;
	--visitedTimes[AL->focus];
	--visitedTimes[index];
}

// Split cmd
void TG::Split(ActiveList* AL, ActiveList* AL1, int index, std::stack<ActiveList*> S) {
	int offset = AL->Split(AL1, index);
	std::string str_offset = std::to_string(offset);
	code += "split" + str_offset;
	// Push the smaller one on stack
	if (AL->active_indices.size() < AL1->active_indices.size()) {
		ActiveList* temp = AL;
		AL = AL1;
		AL1 = AL;
	}
	S.push(AL1);
}

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
int TG::FindUnvisitedTriangle() {
	int i = 1;
	while (visitedTriangles[i++] != 0) {
		if (i > mesh->triangles.size())
			return 0;
	}
	visitedTriangles[i - 1] = 1;
	return i - 1;
}

void TG::Encode() {
	std::stack<ActiveList*> imcomplete_lists;
	ActiveList AL, AL1;
	visitedTriangles = new int[mesh->triangles.size() + 1];
	for (int i = 0; i < mesh->triangles.size() + 1; ++i)
		visitedTriangles[i] = 0;
	visitedVertices = new int[mesh->vertices.size() + 1];
	visitedTimes = new int[mesh->vertices.size() + 1];
	indices = new int[mesh->vertices.size() + 1];
	alreadyErased = new bool[mesh->vertices.size() + 1];
	for (int i = 0; i < mesh->vertices.size() + 1; ++i) {
		visitedVertices[i] = 0;
		visitedTimes[i] = mesh->degrees[i];
		indices[i] = 0;
		alreadyErased[i] = false;
	}

	while (int i = FindUnvisitedTriangle()) {
		--i;
		tri triangle = mesh->triangles[i];
		Add(&AL, triangle.index1);
		Add(&AL, triangle.index2);
		Add(&AL, triangle.index3);
		AL.focus = triangle.index1;
		imcomplete_lists.push(&AL);

		while (!imcomplete_lists.empty()) {
			AL = *imcomplete_lists.top();
			imcomplete_lists.pop();

			TMesh::Node *neighbor = mesh->neighbors[AL.focus];
			while (!AL.Empty()) {
				neighbor = neighbor->next;
				if (!neighbor)
					break;
				if (visitedVertices[neighbor->index] == 0) { // Unvisited
					Add(&AL, neighbor->index);
				}	else {
					if (AL.Contains(neighbor->index)) { // In current AL
						Split(&AL, &AL1, neighbor->index, imcomplete_lists);
					} else { // In some AL on stack
						ActiveList *al = FindOnStack(imcomplete_lists, neighbor->index);
						AL.Merge(al, neighbor->index);
						// Do nothing
						// Do something when treating torus-like meshes
					}
				}
				// Remove full vertices
				for (int i = 0; i < mesh->vertices.size(); ++i) {
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

/*void TG::Decode(TMesh *mesh) {
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
}*/