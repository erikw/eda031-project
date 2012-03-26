#ifndef DIR_ITERATOR_H
#define DIR_ITERATOR_H

#include <sys/types.h>
#include <dirent.h>

#include <iterator>

#include "db/dir_rep.h"

namespace db {
	class DirIterator : public std::iterator<std::forward_iterator_tag, int> {
		friend bool operator==(const DirIterator &lhs, const DirIterator &rhs);
	public:
		explicit DirIterator(DIR *dir);
		DirIterator(const DirIterator &orig);
		DirIterator &operator=(const DirIterator &rhs);
		~DirIterator();
		
		dirent *operator*() { return dir_entity; }
		const dirent *operator*() const { return dir_entity; }
		DirIterator &operator++();
		const DirIterator &operator++() const;
	private:
		DirRep *dir_rep;
		mutable dirent *dir_entity;

	};

	bool operator!=(const DirIterator &lhs, const DirIterator &rhs);
}

#endif
