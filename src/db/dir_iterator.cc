#include <cstdlib>

#include <iostream>
#include "db/dir_iterator.h"

#include "db/dir_rep.h"

using namespace std;

namespace db {
	DirIterator::DirIterator(DIR *dir): dir_rep(new DirRep(dir)), dir_entity(NULL) { 
		if (dir) {
			dir_entity = readdir(dir);
		}
	}

	DirIterator::DirIterator(const DirIterator &orig) : dir_rep(orig.dir_rep), dir_entity(orig.dir_entity) {
		++orig.dir_rep->ref_count;	
		dir_rep = orig.dir_rep;
		dir_entity = orig.dir_entity;
	}

	DirIterator &DirIterator::operator=(const DirIterator &rhs) {
		++rhs.dir_rep->ref_count; // Here so it handles self assignments.
		if (--dir_rep->ref_count == 0) {
			delete dir_entity;
		}
		dir_rep = rhs.dir_rep;
		return *this;
	}

	DirIterator::~DirIterator() {
		if (--dir_rep->ref_count == 0) {
			delete dir_rep;
		}
	}

	DirIterator &DirIterator::operator++() {
		if (dir_entity) {
			dir_entity = readdir(dir_rep->dir);
		}
		return *this;
	}

	const DirIterator &DirIterator::operator++() const {
		if (dir_entity) {
			dir_entity = readdir(dir_rep->dir);
		}
		return *this;
	}

	bool operator==(const DirIterator &lhs, const DirIterator &rhs) {
		return lhs.dir_entity == rhs.dir_entity;
	}

	bool operator!=(const DirIterator &lhs, const DirIterator &rhs) {
		return !(lhs == rhs);
	}
}
