#pragma once
#include <string>
#include <iostream>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;

class TMesh {
public:
  TMesh() {}
	TMesh(std::string file_name) {
		ReadMesh(file_name);
	}
  ~TMesh() {}
  void ReadMesh(std::string file_name);
	int N_Vertices();
	int N_Triangles();
	int Valance(int index);
	bool IsOpen();
private:
	MyMesh mesh;
};


// Read mesh from file, build several
// topological traits and store them in the mesh
void TMesh::ReadMesh(std::string file_name) {
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

	// Triangulate the mesh if it's not triangles
	if (!mesh.is_triangles())
		mesh.triangulate();

	// Calculate and store vertices's valances
	OpenMesh::VPropHandleT<MyMesh::Scalar> valances;
	mesh.add_property(valances);

	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		MyMesh::Scalar valance = 0.0f;

		for (MyMesh::VertexVertexIter vv_it = mesh.vv_iter(*v_it); vv_it; ++vv_it)
			++valance;
		mesh.property(valances, *v_it) = valance;
	}
}


// Return the number of vertices
int TMesh::N_Vertices() {
	return mesh.n_vertices;
}


// Return the number of triangles
int TMesh::N_Triangles() {
	return mesh.n_faces;
}


// Return valance
int TMesh::Valance(int index) {
	OpenMesh::VPropHandleT<MyMesh::Scalar> valance;
	OpenMesh::VertexHandle v_it(index);
	return mesh.property(valance, index);
}


// Return true when mesh is open,
// namely, having boundaries
bool TMesh::IsOpen() {
	bool open = false;
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
		if (mesh.is_boundary(*v_it)) {
			open = true;
			break;
		}
	}
	return open;
}