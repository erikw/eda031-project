#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

#include "db/file_art.h"

using namespace std;

namespace db {
	istream &operator>>(istream &in, FileArt &file_art) {
		in >> file_art.id; // TODO will skip to next line properly?
		getline(in, file_art.title);
		getline(in, file_art.author);
		file_art.text = string((istream_iterator<char>(in)), istream_iterator<char>());
		return in;
	}

	ostream &operator<<(ostream &out, const FileArt &file_art) {
		out << file_art.id << endl;
		out << file_art.title << endl;
		out << file_art.author << endl;
		out << file_art.text;
		return out;
	}
}
