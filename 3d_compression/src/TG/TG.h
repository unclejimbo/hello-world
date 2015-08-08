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

	// Mesh handles
	OpenMesh::VPropHandleT<int> valances;
	OpenMesh::VPropHandleT<int> vCounter;
	OpenMesh::VPropHandleT<bool> vVisited;
	OpenMesh::FPropHandleT<bool> fVisited;

	// Helper functions
	void Add(AList* AL, OpenMesh::VertexHandle v_handle);
	void Split(AList* AL, AList* AL1, int index, std::stack<AList*> S);
	void Merge(AList* AL, AList* AL1, int index);
	bool IsTraversed(OpenMesh::FaceHandle& f_handle);
	bool FreeVertex(OpenMesh::VertexHandle v_handle);
	bool FullVertex(OpenMesh::VertexHandle v_handle);
	AList *FindOnStack(std::stack<AList*> stack, int index);
};


// Read mesh from file, build several
// topological traits and store them in the mesh
void TG::ReadMesh(std::string file_name) {
	// Request vertex normals and read them from file
	// If they're not provided, then calculate them
	mesh.request_vertex_normals();

	if (!mesh.has_vertex_normals()) {
		std::cerr << "Error requiring vertex normals!" << std::endl;
		exit(1);
	}

	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(mesh, file_name, opt)) {
		std::cerr << "read error" << std::endl;
		exit(1);
	}

	if (!opt.check(OpenMesh::IO::Options::VertexNormal)) {
		// Use face normals to update vertex normals
		mesh.request_face_normals();
		mesh.update_normals();
		mesh.release_face_normals();
	}

	// ---------------------------------------
	// TODO : Add dummy vertex if mesh is open
	// ---------------------------------------

	// Triangulate the mesh if it's not triangles
	if (!mesh.is_triangles())
		mesh.triangulate();

	// Calculate and store vertices's valances,
	// and store visited times
	mesh.add_property(valances);
	mesh.add_property(vCounter);
	mesh.add_property(vVisited);

	for (TMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		int valance = 0;
		for (TMesh::VertexVertexIter vv_it = mesh.vv_iter(*v_it); vv_it.is_valid(); ++vv_it)
			++valance;
		mesh.property(valances, *v_it) = valance;
		mesh.property(vCounter, *v_it) = valance;
		mesh.property(vVisited, *v_it) = false;
	}

	// Store the status whether a triangle is visited
	mesh.add_property(fVisited);

	for (TMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
		mesh.property(fVisited, *f_it) = false;
	}

	// Print basic info
	std::cout << file_name << ": " << std::endl
		<< "#vertices:  " << mesh.n_vertices() << std::endl
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
		TMesh::VertexHandle v0_handle = cfv_it++.handle();
		TMesh::VertexHandle v1_handle = cfv_it++.handle();
		TMesh::VertexHandle v2_handle = cfv_it.handle();
		
		Add(&AL, v0_handle);
		Add(&AL, v1_handle);
		Add(&AL, v2_handle);
		AL.focus = v0_handle.idx();
		imcomplete_lists.push(&AL);

		while (!imcomplete_lists.empty()) {
			AL = *imcomplete_lists.top();
			imcomplete_lists.pop();

			// Given a focus vertex, iterate through
			// all its neighbor vertices in ccw order
			// Note that if the initial triangle is 
			//                 v0
			//                /  \
			//               v1--v2
			// and we set v0 as focus, then the iteration
			// should start from v2 to v1
			TMesh::VertexVertexCCWIter vv_ccwit = mesh.vv_ccwiter(v0_handle);
			TMesh::VertexVertexCCWIter vv_end = vv_ccwit;

			while (vv_end->idx() != v1_handle.idx() || vv_end->idx() != v2_handle.idx()) {
				++vv_end;
			}
			vv_ccwit = vv_end; // v1
			++vv_ccwit; // v2


			while (!AL.Empty()) {
				++vv_ccwit;
				if (!vv_ccwit->is_valid())
					vv_ccwit = mesh.vv_ccwiter(v0_handle);
				if (vv_ccwit == vv_end) {
					std::cout << "ERROR::VVIter: This is not supposed to happen!" << std::endl;
					exit(1);
				}

				// If the neighboring vertex hasn't been visited,
				// simply add it to the AL
				int index_debug = vv_ccwit->idx();
				if (FreeVertex(*vv_ccwit))
					Add(&AL, *vv_ccwit);
				// Else the neighboring vertex should either be in the
				// current AL or in another AL on stack
				else {
					if (AL.Contains(vv_ccwit->idx()))
						Split(&AL, &AL1, vv_ccwit->idx(), imcomplete_lists);
					else {
						AList *al = FindOnStack(imcomplete_lists, vv_ccwit->idx());
						Merge(&AL, al, vv_ccwit->idx());
					}
				}

				// Remove full vertices
	   		auto iter_AL = AL.iter();
				for (iter_AL = AL.begin(); iter_AL != AL.end();) {
					int index = *iter_AL;
					TMesh::VertexHandle v_h(index);
					if (mesh.property(vCounter, v_h) == 0) {
						iter_AL = AL.Remove(iter_AL);
					} else
						++iter_AL;
				}

				// If focus is removed, change the focus onto the next one,
				// and deal with the neighbor vertices of the new focus
				if (AL.FocusRemoved()) {
					if (AL.Empty())
						break;
					AL.focus = *AL.begin();
					v0_handle = mesh.vertex_handle(AL.focus);
					vv_ccwit = mesh.vv_ccwiter(v0_handle);
					continue;
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

	int valance = mesh.property(valances, v_handle);
	std::string str_valance = std::to_string(valance);
	code += "add" + str_valance;

	// Mark this vertex as visited
	mesh.property(vVisited, v_handle) = true;

	// Mark this triangle as visited
	TMesh::HalfedgeHandle he_handle = mesh.halfedge_handle(v_handle);
	TMesh::HalfedgeHandle he_ccw_h = mesh.ccw_rotated_halfedge_handle(he_handle);
	TMesh::FaceHandle f_handle = mesh.face_handle(he_ccw_h);
	mesh.property(fVisited, f_handle) = true;

	// The vCounter of every neighbor of index should decrease by one
	TMesh::ConstVertexVertexIter cvv_it = mesh.vv_iter(v_handle);
	for (cvv_it; cvv_it.is_valid(); ++cvv_it) {
		--mesh.property(vCounter, *cvv_it);
	}
}


// Split AL into two because it intersects itself,
// generate code word, and push the smaller AL onto stack
void TG::Split(AList* AL, AList* AL1, int index, std::stack<AList*> S) {
	int offset = AL->Split(AL1, index);

	std::string str_offset = std::to_string(offset);
	code += "split" + str_offset;

	// Exchange AL with AL1 if AL is smaller
	/*if (AL->Size() < AL1->Size()) {
		AList* temp = AL;
		AL = AL1;
		AL1 = temp;
	}*/
	S.push(AL1);

	// The edge is processed
	TMesh::VertexHandle v_handle(index);
	--mesh.property(vCounter, v_handle);
	v_handle = mesh.vertex_handle(AL->focus);
	--mesh.property(vCounter, v_handle);
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


// Return true if the vertex if free,
// which means the vertex is unvisited
bool TG::FreeVertex(OpenMesh::VertexHandle v_handle) {
	return !mesh.property(vVisited, v_handle);
}


// Return true if the vertex if full,
// which means the vertex has been visited #valance times
bool TG::FullVertex(OpenMesh::VertexHandle v_handle) {
	return mesh.property(vCounter, v_handle) == 0;
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

	if (result == nullptr) {
		std::cerr << "Error: bad algorithm" << std::endl;
		exit(1);
	}
	return result;
}