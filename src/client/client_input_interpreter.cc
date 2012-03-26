#include "client/client_input_interpreter.h"

#include <algorithm>
#include <cstring>
#include <cctype>
#include <sstream>
#include <iostream>

#include "db/create_art_query.h"
#include "db/create_ng_query.h"
#include "db/delete_art_query.h"
#include "db/delete_ng_query.h"
#include "db/get_art_query.h"
#include "db/list_art_query.h"
#include "db/list_ng_query.h"

using namespace std;
using namespace db;

namespace client {
	Query *ClientInputInterpreter::recieve_query(const string& line) throw (InputSyntaxError) {
		istringstream iss(line);
		string command;
		iss >> command;

		istringstream iss_check(line);
		string check;
		iss_check >> check;

		if (command.compare("list") == 0 | command.compare("ls") == 0) {
			if (iss_check >> check) {
				return read_list_art(iss);
			} else {
				return read_list_ng(iss);
			}
		} else if (command.compare("create") == 0) {
			size_t id_check;
			if (iss_check >> id_check) {
				return read_create_art(iss);
			} else {
				return read_create_ng(iss);
			}
		} else if (command.compare("delete") == 0 || command.compare("rm") == 0) {
			size_t id_check;
			if (!(iss_check >> id_check)) { // No (valid) parameter.
				throw_exception(LAST);
			} else if (!(iss_check >> id_check)) { // One valid parameter.
				return read_delete_ng(iss);
			} else { // Two valid parameters.
				return read_delete_art(iss);
			}
		} else if (command.compare("read") == 0) {
			return read_get_art(iss);
		} else if (command.compare("help") == 0 || command.compare("?") == 0) {
			print_help();
			return 0;
		} else {
			throw_exception(LAST);
		}
		return 0;
	}

	Query *ClientInputInterpreter::read_list_ng(istringstream &iss) throw (InputSyntaxError) {
		return new ListNGQuery();
	}

	Query *ClientInputInterpreter::read_create_ng(istringstream &iss) throw (InputSyntaxError) {
		string name;
		if (!(iss >> name))
			throw_exception(CREATE_NG);
		if (!iss.eof())
			throw_exception(CREATE_NG);
		return new CreateNGQuery(name);
	}

	Query *ClientInputInterpreter::read_delete_ng(istringstream &iss) throw (InputSyntaxError) {
		int id;
		if (!(iss >> id))
			throw_exception(DELETE_NG);
		if (!iss.eof())
			throw_exception(DELETE_NG);
		return new DeleteNGQuery(id);
	}

	Query *ClientInputInterpreter::read_list_art(istringstream &iss) throw (InputSyntaxError) {
		int id;
		if (!(iss >> id) || !iss.eof()) {
			throw_exception(LIST_ART);
		} 
		return new ListArtQuery(id);
	}

	Query *ClientInputInterpreter::read_create_art(istringstream &iss) throw (InputSyntaxError) {
		string title, author, text;
		int ng_id;
		if (!(iss >> ng_id >> title >> author >> text))
			throw_exception(CREATE_ART);
		//if (!(iss >> ng_id)) {

		//}



		if (!iss.eof())
			throw_exception(CREATE_ART);
		return new CreateArtQuery(ng_id,title, author, text);
	}

	Query *ClientInputInterpreter::read_delete_art(istringstream &iss) throw (InputSyntaxError) {
		int ng_id, art_id;
		if (!(iss >> ng_id >> art_id))
			throw_exception(DELETE_ART);
		if (!iss.eof())
			throw_exception(DELETE_ART);
		return new DeleteArtQuery(ng_id, art_id);
	}


	Query *ClientInputInterpreter::read_get_art(istringstream &iss) throw (InputSyntaxError) {
		int ng_id, art_id;
		if (!(iss >> ng_id >> art_id))
			throw_exception(GET_ART);
		if (!iss.eof())
			throw_exception(GET_ART);
		return new GetArtQuery(ng_id, art_id);
	}

	void ClientInputInterpreter::throw_exception(int command_type) throw (InputSyntaxError) {
		cout << "No such command. ";
		if (command_type != LAST) {
			cout << endl << "Usage: ";
			cout << help_lines[command_type] << endl;
		}
		cout << "Write 'help' for a list of all commands." << endl;
		throw InputSyntaxError();
	}


	void ClientInputInterpreter::print_help(){
		cout << "Available commands:" << endl;
		for (size_t i = 0; i < LAST; ++i)
			cout << "  " << help_lines[i] << endl;
	}

	const string ClientInputInterpreter::help_lines[] = {
		"'list|ls' - List all newsgroups.",
		"'(list|ls) NEWSGROUP_ID' - List all articles in NEWSGROUP_ID.",
		"'create NEWSGROUPNAME' - Create a new newsgroup with title NEWSGROUPNAME.",
		"'create NEWSGROUP_ID TITLE AUTHOR TEXT' - Create an article in NEWSGROUP_ID with title TITLE, author AUTHOR and text TEXT.",
		"'(delete|rm) NEWSGROUP_ID' - Delete newsgroup with id NEWSGROUP_ID.",
		"'(delete|rm) NEWSGROUP_ID' ARTICLE_ID - Delete article with id ARTICLE_ID in newsgroup with id NEWSGROUP_ID.",
		"'read article NEWSGROUP_ID ARTICLE_ID' - Prints article with id ARTICLE_ID in newsgroup with id NEWSGROUP_ID.",
		"'exit|EOF|q' - Exits the program.",
		"'help|?' - This help listing."
	};
}
