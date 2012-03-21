#include "db/dir_iterator.h"

using namespace std;

namespace db {
	DirIterator::DirIterator(DIR *d): dir(d), dir_entity(0) {
		if (dir) {
			dir_entity = readdir(dir);
		}
	}

	DirIterator &DirIterator::operator++() {
		if (dir_entity) {
			dir_entity = readdir(dir);
		}
		return *this;
	}

	bool operator!=(const DirIterator &lhs, const DirIterator &rhs) {
		return !(lhs == rhs);
	}

	bool operator==(const DirIterator &lhs, const DirIterator &rhs) {
		return lhs.dir_entity == rhs.dir_entity;
	}
}
