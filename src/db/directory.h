#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <sys/types.h>
#include <string>

#include "db/dir_iterator.h"

namespace db {
	class Directory {
	public:
		Directory(const std::string &p);
		~Directory() { closedir(dir); }
		typedef DirIterator iterator ;
		//typedef const DirIterator const_iterator; // TODO
		iterator begin() { return DirIterator(dir); }
		//const_iterator begin() const { return DirIterator(dir); }
		iterator end() { return DirIterator(0); }
		//const_iterator end() const { return DirIterator(0); }
		std::string get_path() { return path; }
	private:
		std::string path;
		DIR *dir;
	};
}
#endif
