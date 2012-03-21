#ifndef FILE_ART_H
#define FILE_ART_H

#include <string>
#include <iostream>

namespace db {
	class FileArt {
		friend std::istream &operator>>(std::istream &in, FileArt &file_art);
		friend std::ostream &operator<<(std::ostream &out, const FileArt &file_art);
	public:
		std::string get_title() { return author; }
		std::string get_author() { return author; }
		std::string get_text() { return author; }
	private:
		std::string title;
		std::string author;
		std::string text;
	};
}

#endif
