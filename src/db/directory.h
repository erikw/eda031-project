#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <sys/types.h>
#include <string>
#include <vector>
#include <functional>
#include <dirent.h>

#include "db/dir_iterator.h"

namespace db {
	class Directory {
	public:
		Directory(const std::string &p);
		~Directory() { closedir(dir); }
		typedef DirIterator iterator ;
		//typedef const DirIterator const_iterator; // TODO needed?
		iterator begin() { return DirIterator(dir); }
		//const_iterator begin() const { return DirIterator(dir); }
		iterator end() { return DirIterator(0); }
		//const_iterator end() const { return DirIterator(0); }
		std::string get_path() { return path; }
		std::vector<std::string> list_content();
		void delete_file(const std::string &file_name);
		
		// Create a directory in this directory.
		void mk_dir(const std::string &name);
		bool file_exists(const std::string &file_name);
	private:
		struct equal_file_name : std::binary_function<dirent *, std::string, bool> {
			bool operator()(dirent *dirp, std::string file_name) const {
				return dirp->d_name == file_name;
			}
		};

		void mk_dir_helper(std::string full_path);

		std::string path;
		DIR *dir;
	};
}
#endif
