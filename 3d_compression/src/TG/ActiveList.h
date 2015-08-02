#pragma once
#include <vector>
#include <algorithm>
#include <iterator>

class ActiveList {
public:
	std::vector<int> active_indices;
	int focus;
	void Add(int index);
	int Split(ActiveList *AL, int new_focus);
	void Merge(ActiveList *AL, int new_focus);
	//void RemoveFullVertices();
	bool Empty();
	bool Contains(int index);
};

// Add indices to the activelist using an initializing list
void ActiveList::Add(int index) {
	active_indices.push_back(index);
}

// Split the activelist into two with respect to
// the new_focus, and return the offset between
// the focus and the new_focus
int ActiveList::Split(ActiveList *AL, int new_focus) {
	auto start = std::find(active_indices.begin(),
		active_indices.end(), focus);
	auto stop = std::find(active_indices.begin(),
		active_indices.end(), new_focus);
	if (stop < start) {
		auto temp = stop;
		stop = start;
		start = temp;
	}
	for (auto it = start; it != stop; ++it) {
		AL->active_indices.push_back(*it);
	}
	int offset = stop - start;
	active_indices.erase(start, stop);
	return offset;
}

// Merge *AL into this,
// only happens in torus-like meshes
void ActiveList::Merge(ActiveList *AL, int new_focus) {
	// Do nothing
}

// Return true when AL is empty
bool ActiveList::Empty() {
	return active_indices.empty();
}

// Return true when index is contained in AL
bool ActiveList::Contains(int index) {
	if (std::find(active_indices.begin(), active_indices.end(), index) != active_indices.end())
		return true;
	else
		return false;
}