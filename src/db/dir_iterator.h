#ifndef DIR_ITERATOR_H
#define DIR_ITERATOR_H
#include <sys/types.h>
#include <dirent.h>
#include <iterator>

namespace db {
	class DirIterator : public std::iterator<std::forward_iterator_tag, int> {
		friend bool operator!=(const DirIterator &lhs, const DirIterator &rhs);
	public:
		DirIterator(DIR *dir);
		dirent *operator*() { return dir_entity; }
		//dirent *operator*() const { return dir_entity; }
		DirIterator &operator++();
	private:
		DIR *dir;
		dirent *dir_entity;

	};

	bool operator==(const DirIterator &lhs, const DirIterator &rhs);
}

#endif
