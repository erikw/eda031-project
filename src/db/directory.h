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
		//~Directory() { closedir(dir); }
		typedef DirIterator iterator ;
		//typedef const DirIterator const_iterator; // TODO needed?
		iterator begin(); 

		//const_iterator begin() const { return DirIterator(dir); }
		iterator end() { return DirIterator(0); }
		//const_iterator end() const { return DirIterator(0); }
		std::string get_path() { return path; }

		// Construct the full path to the given file.
		std::string full_path(std::string filename) { return path + "/" + filename; }

		// List all files in directory.
		std::vector<std::string> list_files();
		// List all subdirectories.
		std::vector<std::string> list_dirs();

		// Delete this directory.
		void delete_dir();

		// Delete file in this directory.
		void delete_file(const std::string &file_name);
		
		// Create a directory in this directory.
		void mk_dir(const std::string &name);

		// Check if a file(directory) exists in this directory.
		bool file_exists(const std::string &file_name);

	private:
		struct equal_file_name : std::binary_function<dirent *, std::string, bool> {
			bool operator()(dirent *dirp, std::string file_name) const {
				return dirp->d_name == file_name;
			}
		};

		// Recursively delete directories and files.
		void delete_dir_rec();

		// List entities in this directory of dirent.d_type type.
		std::vector<std::string> list_type(unsigned int ent_type);

		// Open directory.
		DIR *open_dir();

		void mk_dir_helper(std::string full_path);

		// Path to this directory.
		std::string path;
	};
}
#endif
