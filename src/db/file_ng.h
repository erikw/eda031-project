#ifndef FILE_NG_H
#define FILE_NG_H

#include <string>
#include <iostream>
#include "db/file_art.h"
#include "db/directory.h"

namespace db {
	class FileNG {
	public:
		FileNG(Directory d);
		std::vector<std::pair<size_t, std::string> > list_arts();
		FileArt get_art(size_t id);
		void add_art(const FileArt &art);
		void del_art(size_t id);
		static const std::string NG_INFO_NAME;
	private:
		Directory dir;
	};
}

#endif

