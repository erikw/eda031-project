#ifndef FILE_ART_H
#define FILE_ART_H

#include <string>
#include <iostream>

namespace db {
	class FileArt {
		// Construct file_art from stream.
		friend std::istream &operator>>(std::istream &in, FileArt &file_art);
		
		// Write in a readable format.
		friend std::ostream &operator<<(std::ostream &out, const FileArt &file_art);
	public:
		FileArt(size_t i, std::string ti, std::string au, std::string te) : id(i), title(ti), author(au), text(te) {}
		std::string get_title() { return title; }
		std::string get_author() { return author; }
		std::string get_text() { return text; }
	private:
		size_t id;
		std::string title;
		std::string author;
		std::string text;
	};
}

#endif
