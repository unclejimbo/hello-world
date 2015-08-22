#pragma once
#include <string>
#include <iostream>
#include <stack>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "ActiveList.h"

typedef OpenMesh::TriMesh_ArrayKernelT<> TMesh;
typedef ActiveList AList;

class TG {
public:
  TG() {}
	TG(std::string file_name) {
		ReadMesh(file_name);
	}
  ~TG() {}

	// APIs
	void ReadMesh(std::string file_name);
  void EncodeConnectivity();
  void DecodeConnectivity(TMesh*);

private:
	// Data members
	std::string code;
	TMesh mesh;
	std::vector<int> indices;

	// Mesh handles
	OpenMesh::VPropHandleT<int> valances;
	OpenMesh::VPropHandleT<bool> vVisited;
	OpenMesh::EPropHandleT<bool> eVisited;
	OpenMesh::FPropHandleT<bool> fVisited;

	// Helper functions
	void Add(AList* AL, OpenMesh::VertexHandle v_handle);
	void Split(AList* AL, AList* AL1, int index, std::stack<AList*> S);
	void Merge(AList* AL, AList* AL1, int index);
	bool IsTraversed(OpenMesh::FaceHandle& f_handle);
	OpenMesh::HalfedgeHandle FindFreeEdge(OpenMesh::VertexHandle focus_handle, AList& AL, std::stack<AList*> stack);
	bool FreeVertex(OpenMesh::VertexHandle v_handle);
	bool FullVertex(TMesh::VertexHandle v_handle, const AList& AL, std::stack<AList*> stack);
	AList *FindOnStack(std::stack<AList*> stack, int index);
};


// Read mesh from file, build several
// topological traits and store them in the mesh
void TG::ReadMesh(std::string file_name) {
	if (!OpenMesh::IO::read_mesh(mesh, file_name)) {
		std::cerr << "ERROR::ReadMesh : read error" << std::endl;
		system("Pause");
		exit(1);
	}

	// ---------------------------------------
	// TODO : Add dummy vertex if mesh is open
	// ---------------------------------------

	// Triangulate the mesh if it's not triangles
	if (!mesh.is_triangles())
		mesh.triangulate();

	// Vertex property
	mesh.add_property(valances);
	mesh.add_property(vVisited);

	for (TMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		int valance = 0;
		for (TMesh::VertexVertexIter vv_it = mesh.vv_iter(*v_it); vv_it.is_valid(); ++vv_it)
			++valance;
		mesh.property(valances, *v_it) = valance;
		mesh.property(vVisited, *v_it) = false;
	}

	// Edge property
	mesh.add_property(eVisited);

	for (TMesh::EdgeIter e_it = mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it) {
		mesh.property(eVisited, *e_it) = false;
	}

	// Face property
	mesh.add_property(fVisited);

	for (TMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
		mesh.property(fVisited, *f_it) = false;
	}

	// Print basic info
	std::cout << file_name << ": " << std::endl
		<< "#vertices:  " << mesh.n_vertices() << std::endl
		<< "#edges:     " << mesh.n_edges() << std::endl
		<< "#triangles: " << mesh.n_faces() << std::endl;
}


// Encode the mesh using TG algorithm
// store the connectivity encoding commands
// into the string 'code'
void TG::EncodeConnectivity() {
	std::stack<AList*> imcomplete_lists;
	AList AL, AL1;
	TMesh::FaceHandle f_handle; 

	while (!IsTraversed(f_handle)) {
		// Iterate through the initial triangle and Add to AL
		TMesh::ConstFaceVertexIter cfv_it = mesh.cfv_begin(f_handle);
		TMesh::VertexHandle v0_handle = *cfv_it++;
		TMesh::VertexHandle v1_handle = *cfv_it++;
		TMesh::VertexHandle v2_handle = *cfv_it;
		
		Add(&AL, v0_handle);
		Add(&AL, v1_handle);
		Add(&AL, v2_handle);
		imcomplete_lists.push(&AL);

		while (!imcomplete_lists.empty()) {
			AL = *imcomplete_lists.top();
			imcomplete_lists.pop();

			while (!AL.Empty()) {
				TMesh::VertexHandle focus_handle(AL.focus);

				//debug
				std::cout << "1 ring of " << AL.focus << ": ";
				TMesh::VertexVertexCCWIter debug_it = mesh.vv_ccwiter(focus_handle);
				TMesh::VertexVertexCCWIter debug_end = debug_it;
				do {
					std::cout << debug_it->idx() << " ";
					++debug_it;
				} while (debug_it->idx() != debug_end->idx());
				std::cout << std::endl;

				if (!FullVertex(focus_handle, AL, imcomplete_lists)) {
					TMesh::HalfedgeHandle he_handle = FindFreeEdge(focus_handle, AL, imcomplete_lists);
					TMesh::VertexHandle v_handle = mesh.from_vertex_handle(he_handle);

					// If the neighboring vertex hasn't been visited,
					// simply add it to the AL

					//debug
					int debug_idx = v_handle.idx();

					if (FreeVertex(v_handle))
						Add(&AL, v_handle);
					// Else the neighboring vertex should either be in the
					// current AL or in another AL on stack
					else {
						if (AL.Contains(v_handle.idx())) {
							Split(&AL, &AL1, v_handle.idx(), imcomplete_lists);
							continue;
						}
						else {
							AList *al = FindOnStack(imcomplete_lists, v_handle.idx());
							Merge(&AL, al, v_handle.idx());
						}
					}
				}

				// Remove full vertices
				std::deque<int> removes;
	   		auto iter_AL = AL.iter();
				for (iter_AL = AL.begin(); iter_AL != AL.end();) {
					int index = *iter_AL;
					TMesh::VertexHandle v_h(index);
					if (FullVertex(v_h, AL, imcomplete_lists)) {
						removes.push_back(*iter_AL); // Mark first
					}
					++iter_AL;
				}

				// Do removing
				while (!removes.empty()) {
					int index = removes.front();
					removes.pop_front();

					// If focus is removed, change focus to the next neighbor
					if (index == AL.focus) {
						if (AL.Size() == 0)
							break;

						AL.focus = AL.NextNeighbor(AL.focus);
					}

					AL.Remove(index);
				}

				if (AL.Size() >= 3) {
					TMesh::VertexHandle pre_vh = mesh.vertex_handle(AL.PreviousNeighbor(AL.focus));
					TMesh::VertexHandle focus_vh = mesh.vertex_handle(AL.focus);
					TMesh::HalfedgeHandle free_heh = mesh.find_halfedge(pre_vh, focus_vh);
					TMesh::EdgeHandle free_eh = mesh.edge_handle(free_heh);
					mesh.property(eVisited, free_eh) = true;
				}
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


// Add index to AL, generate code word,
// and update vertex properties
void TG::Add(AList* AL, OpenMesh::VertexHandle v_handle) {
	int index = v_handle.idx();
	AL->Add(index);
	indices.push_back(index);

	int valance = mesh.property(valances, v_handle);
	std::string str_valance = std::to_string(valance);
	code += "add" + str_valance + " ";

	// Mark this vertex as visited
	mesh.property(vVisited, v_handle) = true;

	// Only one vertex in AL
	if (AL->Size() == 1)
		AL->focus = index;

	// Two vertices in AL, add one edge
	else if (AL->Size() == 2) {
		TMesh::VertexHandle focus_handle = mesh.vertex_handle(AL->focus);
		TMesh::HalfedgeHandle he_handle = mesh.find_halfedge(focus_handle, v_handle);
		TMesh::EdgeHandle e_handle = mesh.edge_handle(he_handle);
		mesh.property(eVisited, e_handle) = true;
	}

	// Equal to or more than three vertices in AL,
	// compute the one-ring vertices of index and 
	// check whether two adjacent vertices have an edge and have both been visited,
	// if so, add two edges and one triangle
	else {
		TMesh::VertexVertexCWIter vv_cwit = mesh.vv_cwiter(v_handle);
		TMesh::VertexVertexCWIter vv_init = vv_cwit;
		TMesh::VertexVertexCWIter vv_pre = vv_cwit++;
		
		do {
			TMesh::VertexHandle v0 = *vv_pre;
			TMesh::VertexHandle v1 = *vv_cwit;
			TMesh::HalfedgeHandle edge = mesh.find_halfedge(v0, v1);

			if (mesh.property(vVisited, v0) && mesh.property(vVisited, v1) && edge.idx() != -1) {
				TMesh::HalfedgeHandle he0 = mesh.find_halfedge(v0, v_handle);
				TMesh::HalfedgeHandle he1 = mesh.find_halfedge(v_handle, v1);
				TMesh::EdgeHandle e0 = mesh.edge_handle(he0);
				TMesh::EdgeHandle e1 = mesh.edge_handle(he1);
				mesh.property(eVisited, e0) = true;
				mesh.property(eVisited, e1) = true;
				TMesh::FaceHandle tri = mesh.face_handle(he0);
				mesh.property(fVisited, tri) = true;
			}

			++vv_cwit; ++vv_pre;
		} while (vv_pre->idx() != vv_init->idx());
	}
}

/**********************************
*          TODO
***********************************/
// Split AL into two because it intersects itself,
// generate code word, and push the smaller AL onto stack
void TG::Split(AList* AL, AList* AL1, int index, std::stack<AList*> S) {
	// Process the topological info
	TMesh::VertexHandle focus_handle = mesh.vertex_handle(AL->focus);
	TMesh::VertexHandle pre_handle = mesh.vertex_handle(AL->PreviousNeighbor(AL->focus));
	TMesh::VertexHandle inter_handle = mesh.vertex_handle(index);
	TMesh::HalfedgeHandle he0 = mesh.find_halfedge(focus_handle, inter_handle);
	TMesh::HalfedgeHandle he1 = mesh.find_halfedge(inter_handle, pre_handle);
	TMesh::EdgeHandle e0 = mesh.edge_handle(he0);
	TMesh::EdgeHandle e1 = mesh.edge_handle(he1);
	mesh.property(eVisited, e0) = true;
	if (e1.idx() != -1) {
		mesh.property(eVisited, e1) = true;
		TMesh::FaceHandle tri = mesh.face_handle(he1);
		mesh.property(fVisited, tri) = true;
	}

	int offset = AL->Split(AL1, index);

	std::string str_offset = std::to_string(offset);
	code += "split" + str_offset + " ";

	// Exchange AL with AL1 if AL is smaller
	/*if (AL->Size() < AL1->Size()) {
		AList* temp = AL;
		AL = AL1;
		AL1 = temp;
	}*/
	S.push(AL1);
	
	// Move the focus of AL to intersection position
	AL->Remove(AL->focus);
	AL->focus = index;
}


// Merge two AL into one
void TG::Merge(AList* AL, AList* AL1, int index) {
	// --------------------
	// TODO : DO YOUR MERGE
	// --------------------
}


// Return true if every triangle in the mesh is visited,
// and store the FaceHandle if found an unvisited one
bool TG::IsTraversed(OpenMesh::FaceHandle& f_handle) {
	bool traversed = true;
	for (TMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
		if (!mesh.property(fVisited, *f_it)) {
			mesh.property(fVisited, *f_it) = true;
			f_handle = *f_it;
			traversed = false;
			break;
		}
	}
	return traversed;
}


// Return an unvisited HalfedgeHandle in ccw order
OpenMesh::HalfedgeHandle TG::FindFreeEdge(OpenMesh::VertexHandle focus_handle, AList& AL, std::stack<AList*> stack) {
	TMesh::VertexIHalfedgeCCWIter vih_ccwit = mesh.vih_ccwiter(focus_handle);
	
	// Given a focus vertex, iterate through its neighbor vertices in ccw order
	// Note that the iteration should start from the 'previous' edge
	// of focus and stop at the 'next' edge of focus
	// For example, Suppose the initial AL is the following
	//                 v1--v0
	//                 /   |
	//                v2   | 
	//                |    |
	//                v3---v4
	// and we set v0 as focus, then the iteration should start 
	// from v0-v4 to v0-v1 in ccw order
	TMesh::VertexHandle pre_handle(AL.PreviousNeighbor(AL.focus));
	TMesh::HalfedgeHandle he_handle = mesh.find_halfedge(pre_handle, focus_handle);

	//debug
	if (he_handle.idx() == -1) {
		std::cout << "ERROR::FindHalfEdge" << std::endl;
		system("pause");
	}

	while (vih_ccwit->idx() != he_handle.idx())
		++vih_ccwit;
	TMesh::VertexIHalfedgeCCWIter vih_init = ++vih_ccwit;

	do {
		TMesh::HalfedgeHandle he_handle(*vih_ccwit);
		TMesh::EdgeHandle e_handle = mesh.edge_handle(he_handle);
		TMesh::VertexHandle v_handle = mesh.from_vertex_handle(he_handle);
		if (!mesh.property(eVisited, e_handle) && FindOnStack(stack, v_handle.idx()) == nullptr) {
			return he_handle;
		}
		++vih_ccwit;
	} while (vih_ccwit->idx() != vih_init->idx());

	// This is not supposed to happen
	return mesh.halfedge_handle(-1);
}


// Return true if the vertex if free,
// which means the vertex is unvisited
bool TG::FreeVertex(OpenMesh::VertexHandle v_handle) {
	return !mesh.property(vVisited, v_handle);
}


// Return true if the vertex if full,
// which means every edge incident to vertex has been visited,
// except for those in other AL on stack
bool TG::FullVertex(TMesh::VertexHandle v_handle, const AList& AL, std::stack<AList*> stack) {
	TMesh::VertexVertexCCWIter vv_ccwit = mesh.vv_ccwiter(v_handle);
	TMesh::VertexVertexCCWIter vv_init = vv_ccwit;

	do {
		TMesh::VertexHandle vh = *vv_ccwit;
		TMesh::HalfedgeHandle he = mesh.find_halfedge(vh, v_handle);
		TMesh::EdgeHandle edge = mesh.edge_handle(he);
		
		// If the edge hasn't been visited and not on stack, then it's not full
		if (!mesh.property(eVisited, edge) && FindOnStack(stack, v_handle.idx()) == nullptr)
			return false;

		++vv_ccwit;
	} while (vv_ccwit->idx() != vv_init->idx());
	return true;
}


// Return the pointer to the AL contains the split index on stack
AList* TG::FindOnStack(std::stack<AList*> stack, int index) {
	std::stack<AList*> container;
	AList* result = nullptr;

	// Find on stack
	while (!stack.empty()) {
		AList *p = stack.top();
		if (p->Contains(index)) {
			stack.pop();
			result = p;
			break;
		}
		container.push(p);
		stack.pop();
	}

	// Restore stack
	while (!container.empty()) {
		stack.push(container.top());
		container.pop();
	}

	/*if (result == nullptr) {
		std::cerr << "Error::FindOnStack : bad algorithm" << std::endl;
		system("Pause");
		exit(1);
	}*/
	return result;
}