#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>>
#include <iostream>

// Data type definition
typedef struct vec {
	double x;
	double y;
	double z;
};

typedef struct tri {
	int index1;
	int index2;
	int index3;
};

class TMesh {
public:
  TMesh() {}
  ~TMesh() {
    delete[] neighbors;
    delete[] degrees;
  }
  void ReadObj(std::string file_name); // Read from wavefront obj file
	bool IsOpen();
  
  std::vector<vec> vertices;
  std::vector<tri> triangles;
	std::vector<int> boundary_indices;
	int* degrees; // Index start from 1
  typedef struct Node {
    int index;
    Node *next;
	} *NeighborList;
  NeighborList* neighbors; // With head node
private:
  void buildTopo();
	void maintainCCW(int index_focus, int index_neighbor);
	int *vertex_count;
};

// Read from wavefront obj file
void TMesh::ReadObj(std::string file_name) {
	std::ifstream ifs(file_name.c_str());
	if (ifs.fail()) {
		std::cout << "Open Failed" << std::endl;
		exit(-1);
	}

	int line_no = 0;
	std::string line, first;
	while (getline(ifs, line)) {
		++line_no;
		std::istringstream iss(line);
		iss >> first;
		if (first == "v") { // Read vertex
			std::string x_str, y_str, z_str;
			iss >> x_str >> y_str >> z_str;
			double x, y, z;
			x = std::stod(x_str);
			y = std::stod(y_str);
			z = std::stod(z_str);
			vec v = { x, y, z };
			this->vertices.push_back(v);
		}
		else if (first == "f") { // Read face
			int v_indices[3];
			for (int i = 0; i < 3; ++i) {
				std::string temp;
				iss >> temp;
				auto split = temp.find_first_of("/");
				std::string str = temp.substr(0, split);
				int v_index = std::stoi(str);
				v_indices[i] = v_index;
			}
			tri triangle = { v_indices[0], v_indices[1], v_indices[2] };
			this->triangles.push_back(triangle);
		}
		else {
			// Blank
		}
		line.clear();
		first.clear();
	}
	ifs.close();

	// Maintain boundary information
	vertex_count = new int[vertices.size() + 1];
	for (int i = 0; i < vertices.size() + 1; ++i)
		vertex_count[i] = 0;
	for (auto it = triangles.begin(); it != triangles.end(); ++it) {
		++vertex_count[it->index1];
		++vertex_count[it->index2];
		++vertex_count[it->index3];
	}
	for (int i = 0; i < vertices.size() + 1; ++i) {
		// For a manifold mesh, if a vertex appears only once, 
		// it's on the boundary
		if (vertex_count[i] == 1) {
			boundary_indices.push_back(i);
		}
	}

	buildTopo();
}

// Traverse triangles to build topological information
void TMesh::buildTopo() {
	auto v_count = vertices.size();
	neighbors = new NeighborList[v_count + 1];
	for (int i = 0; i < v_count + 1; ++i) {
		neighbors[i] = new Node();
	}
	degrees = new int[v_count + 1];
	for (int i = 0; i < v_count + 1; ++i) {
		degrees[i] = 0;
	}

	for (auto it = triangles.begin(); it != triangles.end(); ++it) {
		int index1 = (*it).index1, index2 = (*it).index2, index3 = (*it).index3;
		NeighborList v1_neighbors = neighbors[index1];
		NeighborList v2_neighbors = neighbors[index2];
		NeighborList v3_neighbors = neighbors[index3];

		maintainCCW(index1, index2);
		maintainCCW(index1, index3);
		maintainCCW(index2, index1);
		maintainCCW(index2, index3);
		maintainCCW(index3, index1);
		maintainCCW(index3, index2);
	}
}

// Update neighborList and maintain neighbors in ccw order
void TMesh::maintainCCW(int index_focus, int index_neighbor) {
	NeighborList my_neighbors = neighbors[index_focus];
	++degrees[index_focus];
	if (!my_neighbors->next) {
		Node* node = new Node();
		node->index = index_neighbor;
		my_neighbors->next = node;
	}
	else {
		Node* current = my_neighbors->next;
		Node* previous = my_neighbors;
		bool neighbor_in = false; // Check if neighbor is already in the list
		bool insert_done = false; // Mark insertion success
		vec focus = vertices[index_focus - 1];
		vec neighbor = vertices[index_neighbor - 1];
		vec vec_neighbor = { neighbor.x - focus.x, neighbor.y - focus.y, 0 };
		while (current) {
			if (current->index == index_neighbor) {
				neighbor_in = true;
				--degrees[index_focus];
				break;
			}
			vec cursor = vertices[current->index - 1];
			vec vec_cursor = { cursor.x - focus.x, cursor.y - focus.y, 0 };
			double cross = vec_cursor.x * vec_neighbor.y - vec_cursor.y * vec_neighbor.x;
			if (cross < 0) { // Insert neighbor before temp
				Node* node = new Node();
				node->index = index_neighbor;
				node->next = current;
				previous->next = node;
				insert_done = true;
				break;
			}
			previous = current;
			current = current->next;
		}
		// If neighbor isn't on the list but not in ccw order
		// with respect to other vertices on the list, then
		// insert neighbor to the end
		if (!neighbor_in && !insert_done) {
			Node* node = new Node();
			node->index = index_neighbor;
			previous->next = node;
		}
	}
}

bool TMesh::IsOpen() {
	return boundary_indices.empty();
}