#ifndef CLIENTINPUTINTERPRETER_H
#define CLIENTINPUTINTERPRETER_H

#include <string>
#include <sstream>

#include "db/query.h"

namespace client {
	struct InputSyntaxError {};

	class ClientInputInterpreter {
	public:
		ClientInputInterpreter() {};
		db::Query *recieve_query(const std::string& line) throw (InputSyntaxError);
	private:
		enum { LIST_NG, LIST_ART, CREATE_NG, CREATE_ART,
			DELETE_NG, DELETE_ART, GET_ART, EXIT, HELP, LAST
		};

		static const std::string help_lines[];

		db::Query *read_list_ng() throw (InputSyntaxError);
		db::Query *read_create_ng() throw (InputSyntaxError);
		db::Query *read_delete_ng(std::istringstream &iss) throw (InputSyntaxError);
		db::Query *read_list_art(std::istringstream &iss) throw (InputSyntaxError);
		db::Query *read_create_art(std::istringstream &iss) throw (InputSyntaxError);
		db::Query *read_delete_art(std::istringstream &iss) throw (InputSyntaxError);
		db::Query *read_get_art(std::istringstream &iss) throw (InputSyntaxError);
		void print_help();
		void throw_exception(int type) throw (InputSyntaxError);
	};
}

#endif
