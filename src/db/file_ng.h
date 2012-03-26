#ifndef FILE_NG_H
#define FILE_NG_H

#include <string>
#include <iostream>

#include "db/file_art.h"
#include "db/directory.h"

namespace db {
	class FileNG {
	public:
		// Exception.
		struct InexistingArticle {};

		explicit FileNG(Directory d);
		
		std::vector<std::pair<size_t, std::string> > list_arts() const;
		FileArt *get_art(size_t id) const throw(InexistingArticle);
		void add_art(const std::string &title, const std::string &author, const std::string &text);
		void del_art(size_t id);
		void del_ng();

	private:
		static const std::string NG_INFO_NAME;

		// Read and increment ID counter.
		size_t next_id();

		Directory dir;
	};
}

#endif

