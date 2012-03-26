#include <cstring>
#include <sstream>
#include <iostream>

#include "client/client_input_interpreter.h"
#include "db/list_ng_query.h"
#include "db/create_ng_query.h"
#include "db/delete_ng_query.h"
#include "db/list_art_query.h"
#include "db/create_art_query.h"
#include "db/delete_art_query.h"
#include "db/get_art_query.h"

/*list groups
list articles snum
create group string
create article num string
delete group num
delete article num num
read article num num
*/

namespace client {
	using namespace db;
	using namespace std;


	Query *ClientInputInterpreter::recieve_query(const string& line) throw (InputSyntaxError){		
		istringstream iss(line);
		string command;
		string command_type;
		iss >> command;
		iss >> command_type;
		if(command.compare("list")==0) {
			if (command_type.compare("articles")==0)
				return read_list_art(iss);
			else if (command_type.compare("groups")==0)
				return read_list_ng(iss);
			else
				throw_exception(LAST);
		} else if(command.compare("create")==0) {
			if (command_type.compare("article")==0)
				return read_create_art(iss);
			else if (command_type.compare("group")==0)
				return read_create_ng(iss);
			else
				throw_exception(LAST);	
		} else if(command.compare("delete")==0) {
			if (command_type.compare("article")==0)
				return read_delete_art(iss);
			else if (command_type.compare("group")==0)
				return read_delete_ng(iss);
			else
				throw_exception(LAST);
		} else if(command.compare("get")==0) {
			if (command_type.compare("article")==0)
				return read_get_art(iss);
			else
				throw_exception(LAST);
		} else if(command.compare("help")==0) {
			print_help();
			return 0;
		} else {
			throw_exception(LAST);
		}
		return 0;
		
	}

	Query *ClientInputInterpreter::read_list_ng(istringstream &iss) throw (InputSyntaxError) {
		if (!iss.eof())
			throw_exception(LIST_NG);	
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
		if (!(iss >> id))		
			throw_exception(LIST_ART);
		if (!iss.eof())
			throw_exception(LIST_ART);
		return new ListArtQuery(id);
	}


	Query *ClientInputInterpreter::read_create_art(istringstream &iss) throw (InputSyntaxError) {
		string title, author, text;
		int ng_id;
		if (!(iss >> ng_id >> title >> author >> text))
			throw_exception(CREATE_ART);
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
		cout << "Syntax error: no such command." << endl;
		if (command_type != LAST){
			cout << "Usage: ";
			cout << help_lines[command_type] << endl;
		}
		cout << "Write 'help' for a list of all commands." << endl;
		throw InputSyntaxError();
	}


	void ClientInputInterpreter::print_help(){
		cout << "Usage: " << help_lines[0] << endl;
		for(size_t i = 1; i < LAST; ++i)
			cout << "  or:  " << help_lines[i] << endl; 
	}
	
	const string ClientInputInterpreter::help_lines[] = { 
			"'list groups' - List all newsgroups.",
			"'list articles NEWSGROUP_ID' - List all articles in NEWSGROUP_ID.",
			"'create group NEWSGROUP' - Create a new newsgroup with title NEWSGROUP.",
			"'create article NEWSGROUP_ID TITLE AUTHOR TEXT' - Create an article in NEWSGROUP_ID with title TITLE, author AUTHOR and text TEXT",
			"'delete group NEWSGROUP_ID' - delete newsgroup with id NEWSGROUP_ID",
			"'delete article NEWSGROUP_ID' ARTICLE_ID - delete article with id ARTICLE_ID in newsgroup with id NEWSGROUP_ID",
			"'get article NEWSGROUP_ID ARTICLE_ID' - prints article with id ARTICLE_ID in newsgroup with id NEWSGROUP_ID" };
	
	
}
