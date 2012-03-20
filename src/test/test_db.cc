#include "db/memory_db.h"
#include "net/connection.h"
#include "net/protocol.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace db;
using namespace net;

class MockConnection : public Connection {
	public:
		MockConnection() {}
		virtual ~MockConnection() {}
		virtual bool isConnected() const {
			return true;
		}

		virtual void write(unsigned char ch) const throw(ConnectionClosedException) {
			output.push_back(ch);
		}
		
		virtual unsigned char read() const throw(ConnectionClosedException) {
			return 0;
		}

		vector<char> get_output() {
			return output;
		}

		void clear_output(){
			output.clear();
		}

	private:
		size_t read_at;
		mutable vector<char> output;
};

MemoryDB *mdb;
MockConnection con = MockConnection();

template<typename T>
void assertEquals(const string& if_neq, const T& expected, const T& value) {
	if(!equal(expected.begin(), expected.end(), value.begin())){
		cout << if_neq << endl;
		cout << "Was [";
		typename T::const_iterator it = value.begin();
		for (; it != value.end(); ++it) {
			cout << *it << endl;
		}
		cout << "] but expected [";
		for (it = expected.begin(); it != expected.end(); ++it) {
			cout << *it << endl;
		}
		cout << "]." << endl;
	}
}

void convert(vector<char>& out, unsigned int num){
	out.push_back(static_cast<char>((num << 24) & 0xFF));
	out.push_back(static_cast<char>((num << 16) & 0xFF));
	out.push_back(static_cast<char>((num << 8) & 0xFF));
	out.push_back(static_cast<char>(num & 0xFF));
}

void convert(vector<char>& out, string str){
	convert(out, str.size());
	for(size_t i = 0; i < str.size(); ++i){
		out.push_back(str[i]);
	}
}

void set_up(){
	mdb = new MemoryDB();
	con = MockConnection();
}

void tear_down(){
	delete mdb;
}

void test_create_ng(){
	set_up();
	cout << "Test create newsgroup" << endl;
	Result *res = mdb->create_ng("test_ng1");
	res->printToConnection(con);
	vector<char> exp;
	exp.push_back(Protocol::ANS_CREATE_NG);
	exp.push_back(Protocol::ANS_ACK);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Incorrect result when creating new newsgroup.", exp, con.get_output());
	delete res;
	tear_down();
}

void test_create_exist_ng(){
	set_up();
	cout << "Test create existing newsgroup" << endl;
	Result *res;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->create_ng("test_ng1");
	res->printToConnection(con);
	vector<char> exp;
	exp.push_back(Protocol::ANS_CREATE_NG);
	exp.push_back(Protocol::ANS_NAK);
	exp.push_back(Protocol::ERR_NG_ALREADY_EXISTS);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Incorrect result when creating existing newsgroup.",
			exp, con.get_output());
	delete res;
	tear_down();
}

void test_list_ng(){
	set_up();
	cout << "Test list existing newsgroups" << endl;
	Result *res;
	vector<char> exp;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->create_ng("test_ng2");
	delete res;
	res = mdb->list_ng();
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_LIST_NG);
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 2);
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 1);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, "test_ng1");
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 2);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, "test_ng2");
	exp.push_back(Protocol::ANS_END);
	assertEquals("List newsgroup.", exp, con.get_output());
	delete res;
	tear_down();
}

void test_list_no_ng(){
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test list no newsgroup." << endl;
	res = mdb->list_ng();
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_LIST_NG);
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 0);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Listing no newsgroups.", exp, con.get_output());
	delete res;
	tear_down();
}

void test_delete_ng(){
	set_up();
	Result *res;
	vector<char> del_exp;
	cout << "Test delete single newsgroup." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->delete_ng(1);
	res->printToConnection(con);
	del_exp.push_back(Protocol::ANS_DELETE_NG);
	del_exp.push_back(Protocol::ANS_ACK);
	del_exp.push_back(Protocol::ANS_END);
	assertEquals("Delete newsgroup", del_exp, con.get_output());
	delete res;
	vector<char> list_exp;
	res = mdb->list_ng();
	con.clear_output();
	res->printToConnection(con);
	list_exp.push_back(Protocol::ANS_LIST_NG);
	list_exp.push_back(Protocol::PAR_NUM);
	convert(list_exp, 0);
	list_exp.push_back(Protocol::ANS_END);
	assertEquals("Listing no newsgroups.", list_exp, con.get_output());
	tear_down();
}

void test_delete_nonexist_ng(){
	set_up();
	Result *res;
	vector<char> del_exp;
	cout << "Test delete non-existing newsgroup." << endl;
	res = mdb->delete_ng(1);
	res->printToConnection(con);
	del_exp.push_back(Protocol::ANS_DELETE_NG);
	del_exp.push_back(Protocol::ANS_NAK);
	del_exp.push_back(Protocol::ERR_NG_DOES_NOT_EXIST);
	del_exp.push_back(Protocol::ANS_END);
	assertEquals("Delete newsgroup", del_exp, con.get_output());
	delete res;
	tear_down();
}

void test_create_art(){
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test create single article." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	string title("test_title");
	string author("test_author");
	string text("test_text");
	res = mdb->create_art(1, title, author, text);
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_CREATE_ART);
	exp.push_back(Protocol::ANS_ACK);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Create article", exp, con.get_output());
	delete res;
	tear_down();
}

void test_create_no_ng_art(){
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test create article without newsgroup." << endl;
	string title("test_title");
	string author("test_author");
	string text("test_text");
	res = mdb->create_art(1, title, author, text);
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_CREATE_ART);
	exp.push_back(Protocol::ANS_NAK);
	exp.push_back(Protocol::ERR_NG_DOES_NOT_EXIST);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Create no ng article", exp, con.get_output());
	delete res;
	tear_down();
}

void test_list_art(){
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test list two articles." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	string title1("test_title1");
	string author("test_author");
	string text("test_text");
	res = mdb->create_art(1, title1, author, text);
	delete res;
	string title2("test_title2");
	res = mdb->create_art(1, title2, author, text);
	delete res;
	res = mdb->list_art(1);
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_LIST_ART);
	exp.push_back(Protocol::ANS_ACK);
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 2);
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 1);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, title1);
	exp.push_back(Protocol::PAR_NUM);
	convert(exp, 2);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, title2);
	exp.push_back(Protocol::ANS_END);
	assertEquals("List article", exp, con.get_output());
	delete res;
	tear_down();
}

void test_list_no_art(){
	set_up();
	Result *res;
	string exp;
	cout << "Test list no articles." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->list_art(1);
	res->printToConnection(con);
	exp += Protocol::ANS_LIST_ART;
	exp += Protocol::ANS_ACK;
	exp += Protocol::PAR_NUM;
	convert(exp, 0);
	exp += Protocol::ANS_END;
	assertEquals("List article should be empty", exp, con_output);
	delete res;
	tear_down();
}

void test_list_no_ng_art(){
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test list article without newsgroup." << endl;
	string title("test_title");
	string author("test_author");
	string text("test_text");
	res = mdb->list_art(1);
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_LIST_ART);
	exp.push_back(Protocol::ANS_NAK);
	exp.push_back(Protocol::ERR_NG_DOES_NOT_EXIST);
	exp.push_back(Protocol::ANS_END);
	assertEquals("List no ng article", exp, con.get_output());
	delete res;
	tear_down();
}

void test_get_art() {
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test to get an article from a news group." << endl;
	int group_id = 1;
	delete mdb->create_ng("ng1");
	string title("Title");
	string author("Author");
	string text("content-text.");
	delete mdb->create_art(group_id, title, author, text);
	res = mdb->get_art(group_id, 1); // First entry should have ID 1.
	res->printToConnection(con);

	exp.push_back(Protocol::ANS_GET_ART);
	exp.push_back(Protocol::ANS_ACK);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, title);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, author);
	exp.push_back(Protocol::PAR_STRING);
	convert(exp, text);
	exp.push_back(Protocol::ANS_END);

	assertEquals("Get article.", exp, con.get_output());
	delete res;
	tear_down();
}

void test_get_no_art() {
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test to get an article that does not exists." << endl;
	delete mdb->create_ng("ng1");
	int group_id = 1;
	string title("Title");
	string author("Author");
	string text("content-text.");
	delete mdb->create_art(group_id, title, author, text);
	res = mdb->get_art(group_id, 2); // First entry should have ID 1.
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_GET_ART);
	exp.push_back(Protocol::ANS_NAK);
	exp.push_back(Protocol::ERR_ART_DOES_NOT_EXIST);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Get inexisting article.", exp, con.get_output());
	delete res;
	tear_down();
}

void test_get_art_no_ng() {
	set_up();
	Result *res;
	vector<char> exp;
	cout << "Test to get an article from inexisting news group." << endl;
	delete mdb->create_ng("ng1");
	int group_id = 1;
	string title("Title");
	string author("Author");
	string text("content-text.");
	delete mdb->create_art(group_id, title, author, text);
	res = mdb->get_art(2, 1);
	res->printToConnection(con);
	exp.push_back(Protocol::ANS_GET_ART);
	exp.push_back(Protocol::ANS_NAK);
	exp.push_back(Protocol::ERR_NG_DOES_NOT_EXIST);
	exp.push_back(Protocol::ANS_END);
	assertEquals("Get article from inexisting news group.", exp, con.get_output());
	delete res;
	tear_down();
}

void test_delete_art(){
	set_up();
	Result *res;
	string exp;
	cout << "Test delete articles." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	string title("test_title1");
	string author("test_author");
	string text("test_text");
	res = mdb->create_art(1, title, author, text);
	delete res;
	res = mdb->delete_art(1, 1);
	con_output = string();
	res->printToConnection(con);
	exp += Protocol::ANS_DELETE_ART;
	exp += Protocol::ANS_ACK;
	exp += Protocol::ANS_END;
	assertEquals("Delete article", exp, con_output);
	delete res;
	con_output = string();
	exp = string();
	res = mdb->list_art(1);
	res->printToConnection(con);
	exp += Protocol::ANS_LIST_ART;
	exp += Protocol::ANS_ACK;
	exp += Protocol::PAR_NUM;
	convert(exp, 0);
	exp += Protocol::ANS_END;
	assertEquals("List article should be empty", exp, con_output);
	delete res;
	tear_down();
}

void test_delete_art_no_ng(){
	set_up();
	Result *res;
	string exp;
	cout << "Test delete article without newsgroup." << endl;
	res = mdb->delete_art(1, 1);
	res->printToConnection(con);
	exp += Protocol::ANS_DELETE_ART;
	exp += Protocol::ANS_NAK;
	exp += Protocol::ERR_NG_DOES_NOT_EXIST;
	exp += Protocol::ANS_END;
	assertEquals("Delete no ng article", exp, con_output);
	delete res;
	tear_down();
}

void test_delete_art_no_art(){
	set_up();
	Result *res;
	string exp;
	cout << "Test delete nonexisting article." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->delete_art(1, 1);
	res->printToConnection(con);
	exp += Protocol::ANS_DELETE_ART;
	exp += Protocol::ANS_NAK;
	exp += Protocol::ERR_ART_DOES_NOT_EXIST;
	exp += Protocol::ANS_END;
	assertEquals("Delete no ng article", exp, con_output);
	delete res;
	tear_down();
}

int main() {
	test_create_ng();
	test_create_exist_ng();
	test_list_ng();
	test_list_no_ng();
	test_delete_ng();
	test_delete_nonexist_ng();
	test_create_art();
	test_create_no_ng_art();
	test_list_art();
	test_list_no_art();
	test_list_no_ng_art();
	test_delete_art();
	test_delete_art_no_ng();
	test_delete_art_no_art();
	test_get_art();
	test_get_no_art();
	test_get_art_no_ng();
}
