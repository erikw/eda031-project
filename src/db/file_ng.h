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
		
		// Exception.
		struct InexistingArticle {};

		std::vector<std::pair<size_t, std::string> > list_arts();
		FileArt *get_art(size_t id) throw(InexistingArticle);
		void add_art(const std::string &title, const std::string &author, const std::string &text);
		void add_art(const FileArt &art);
		void del_art(size_t id);
		void del_ng();

	private:

		// Read and increment ID counter.
		size_t next_id();
		static const std::string NG_INFO_NAME;
		Directory dir;
	};
}

#endif

