#pragma once
#include <vector>
#include <algorithm>
#include <iterator>

class ActiveList {
public:
	ActiveList() {}
	~ActiveList() {}

	// Public Data members
	int focus;
	void Add(int index);

	// APIs
	int Split(ActiveList *AL1, int intersection);
	void Merge(ActiveList *AL, int new_focus);
	bool Empty();
	bool Contains(int index);
	int Size();
	int NextNeighbor(int index);
	int PreviousNeighbor(int index);
	std::vector<int>::iterator Remove(int index);
	std::vector<int>::iterator Remove(std::vector<int>::iterator iter);
	bool FocusRemoved();
	std::vector<int>::iterator iter();
	std::vector<int>::iterator begin();
	std::vector<int>::iterator end();

private:
	std::vector<int> active_indices;
};


// Add indices to the activelist 
inline void ActiveList::Add(int index) {
	active_indices.push_back(index);
}


// Split the activelist into two with respect to
// the new_focus, and return the offset between
// the focus and the new_focus along AL in ccw order
// Note that focus and intersection should both appear
// in AL and AL1 to ensure AL1 has at least 3 vertices
inline int ActiveList::Split(ActiveList *AL1, int intersection) {
	auto start = std::find(active_indices.begin(), active_indices.end(), intersection);
	auto stop = std::find(active_indices.begin(), active_indices.end(), focus);
	int offset = 0;

	// Copy inner items from AL to AL1
	for (auto it = start; it != stop;) {
		// Handling off end condition
		if (it == active_indices.end()) {
			it = active_indices.begin();
			if (it == stop)
				break;
		}
		++offset;
		AL1->active_indices.push_back(*it++);
	}
	AL1->active_indices.push_back(*stop);

	// Delete those items from AL
	if (start <= stop) {
		active_indices.erase(++start, stop);
	}
	// Handling off end condition
	else {
		if (++start == active_indices.end()) {
			start = active_indices.begin();
			active_indices.erase(start, stop);
		} else {
			active_indices.erase(start, active_indices.end());
			active_indices.erase(active_indices.begin(), stop);
		}
	}

	// Inherit focus
	AL1->focus = focus;

	return offset;
}


// Merge *AL into this,
// only happens in torus-like meshes
inline void ActiveList::Merge(ActiveList *AL, int new_focus) {
	// Do nothing
	return;
}


// Return true when AL is empty
inline bool ActiveList::Empty() {
	return active_indices.empty();
}


// Return true when index is contained in AL
inline bool ActiveList::Contains(int index) {
	if (std::find(active_indices.begin(), active_indices.end(), index) != active_indices.end())
		return true;
	else
		return false;
}


// Return the size of AL
inline int ActiveList::Size() {
	return active_indices.size();
}


// Return the index to the next neighbor
inline int ActiveList::NextNeighbor(int index) {
	auto iter = active_indices.begin();
	while (iter != active_indices.end() && *iter != index) {
		++iter;
	}
	if (iter == active_indices.end())
		return NULL;
	if (++iter == active_indices.end())
		iter = active_indices.begin();
	return *(iter);
}


// Return the index to the previous neighbor
inline int ActiveList::PreviousNeighbor(int index) {
	auto r_iter = active_indices.rbegin();
	while (r_iter != active_indices.rend() && *r_iter != index) {
		++r_iter;
	}
	if (r_iter == active_indices.rend())
		return NULL;
	if (++r_iter == active_indices.rend())
		r_iter = active_indices.rbegin();
	return *(r_iter);
}


// Remove index from active_indices
inline std::vector<int>::iterator ActiveList::Remove(int index) {
	auto iter = std::find(active_indices.begin(), active_indices.end(), index);
	if (iter == active_indices.end())
		return iter;
	return active_indices.erase(iter);
}

inline std::vector<int>::iterator ActiveList::Remove(std::vector<int>::iterator iter) {
	return active_indices.erase(iter);
}


// Return true if focus is removed
inline bool ActiveList::FocusRemoved() {
	return std::find(active_indices.begin(), active_indices.end(), focus) == active_indices.end();
}


// Return a iterator for AL
inline std::vector<int>::iterator ActiveList::iter() {
	std::vector<int>::iterator iter;
	return iter;
}


// Return the begin iterator for AL
inline std::vector<int>::iterator ActiveList::begin() {
	return active_indices.begin();
}


// Return the end iterator for AL
inline std::vector<int>::iterator ActiveList::end() {
	return active_indices.end();
}
