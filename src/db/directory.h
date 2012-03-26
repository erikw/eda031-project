#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <sys/types.h>
#include <dirent.h>

#include <string>
#include <vector>
#include <functional>

#include "db/dir_iterator.h"

namespace db {
	class Directory {
	public:
		typedef DirIterator iterator ;
		typedef const DirIterator const_iterator; 

		explicit Directory(const std::string &p);
		
		iterator begin(); 
		iterator end() { return DirIterator(0); }
		const_iterator begin() const;
		const_iterator end() const { return DirIterator(0); }

		std::string get_path() const { return path; }

		// Construct the full path to the given file.
		std::string full_path(std::string filename) const { return path + "/" + filename; }

		// List all files in directory.
		std::vector<std::string> list_files() const;

		// List all subdirectories.
		std::vector<std::string> list_dirs() const;

		// Delete this directory.
		void delete_dir();

		// Delete file in this directory.
		void delete_file(const std::string &file_name);
		
		// Create a directory in this directory.
		void mk_dir(const std::string &name);

		// Check if a file(directory) exists in this directory.
		bool file_exists(const std::string &file_name) const;

	private:
		struct equal_file_name : std::binary_function<dirent *, std::string, bool> {
			bool operator()(dirent *dirp, std::string file_name) const {
				return dirp->d_name == file_name;
			}
		};

		// Recursively delete directories and files.
		void delete_dir_rec();

		// List entities in this directory of dirent.d_type type.
		std::vector<std::string> list_type(unsigned int ent_type) const;

		// Open directory.
		DIR *open_dir() const;

		void mk_dir_helper(std::string full_path) const;

		// Path to this directory.
		std::string path;
	};
}

#endif
