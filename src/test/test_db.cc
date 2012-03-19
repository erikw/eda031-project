
#include "db/memory_db.h"
#include "net/connection.h"
#include "net/protocol.h"
#include <string>
#include <iostream>
using namespace std;
using namespace db;
using namespace net;

string con_output = string();

class MockConnection : public Connection {
	public:
		MockConnection() {}
		virtual ~MockConnection() {}
		virtual bool isConnected() const {
			return true;
		}

		virtual void write(unsigned char ch) const throw(ConnectionClosedException) {
			con_output += ch;
		}
		
		virtual unsigned char read() const throw(ConnectionClosedException) {
			return 0;
		}

	private:
		size_t read_at;
};

MemoryDB *mdb;
MockConnection con = MockConnection();

template<typename T>
void assertEquals(const string& if_neq, const T& expected, const T& value) {
	if(expected != value){
		cout << if_neq << endl;
		cout << "Was [" << value << "] but expected [" << expected << "]." << endl;
	}
}

void convert(string& out, unsigned int num){
	out += static_cast<char>((num << 24) & 0xFF);
	out += static_cast<char>((num << 16) & 0xFF);
	out += static_cast<char>((num << 8) & 0xFF);
	out += static_cast<char>(num & 0xFF);
}

void convert(string& out, string str){
	convert(out, str.size());
	out += str;
}

void set_up(){
	mdb = new MemoryDB();
}

void tear_down(){
	delete mdb;
	con_output.clear();
}

void test_create_ng(){
	set_up();
	cout << "Test create newsgroup" << endl;
	Result *res = mdb->create_ng("test_ng1");
	res->printToConnection(con);
	string exp;
	exp += Protocol::ANS_CREATE_NG;
	exp += Protocol::ANS_ACK;
	exp += Protocol::ANS_END;
	assertEquals("Incorrect result when creating new newsgroup.", exp, con_output);
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
	string exp;
	exp += Protocol::ANS_CREATE_NG;
	exp += Protocol::ANS_NAK;
	exp += Protocol::ERR_NG_ALREADY_EXISTS;
	exp += Protocol::ANS_END;
	assertEquals("Incorrect result when creating existing newsgroup.",
			exp, con_output);
	delete res;
	tear_down();
}

void test_list_ng(){
	set_up();
	cout << "Test list existing newsgroups" << endl;
	Result *res;
	string exp;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->create_ng("test_ng2");
	delete res;
	res = mdb->list_ng();
	res->printToConnection(con);
	exp += Protocol::ANS_LIST_NG;
	exp += Protocol::PAR_NUM;
	convert(exp, 2);
	exp += Protocol::PAR_NUM;
	convert(exp, 1);
	exp += Protocol::PAR_STRING;
	convert(exp, "test_ng1");
	exp += Protocol::PAR_NUM;
	convert(exp, 2);
	exp += Protocol::PAR_STRING;
	convert(exp, "test_ng2");
	exp += Protocol::ANS_END;
	assertEquals("List newsgroup.", exp, con_output);
	delete res;
	tear_down();
}

void test_list_no_ng(){
	set_up();
	Result *res;
	string exp;
	cout << "Test list no newsgroup." << endl;
	res = mdb->list_ng();
	res->printToConnection(con);
	exp += Protocol::ANS_LIST_NG;
	exp += Protocol::PAR_NUM;
	convert(exp, 0);
	exp += Protocol::ANS_END;
	assertEquals("Listing no newsgroups.", exp, con_output);
	delete res;
	tear_down();
}

void test_delete_ng(){
	set_up();
	Result *res;
	string del_exp;
	cout << "Test delete signle newsgroup." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	res = mdb->delete_ng(1);
	res->printToConnection(con);
	del_exp += Protocol::ANS_DELETE_NG;
	del_exp += Protocol::ANS_ACK;
	del_exp += Protocol::ANS_END;
	assertEquals("Delete newsgroup", del_exp, con_output);
	con_output = string();
	delete res;
	string list_exp;
	res = mdb->list_ng();
	res->printToConnection(con);
	list_exp += Protocol::ANS_LIST_NG;
	list_exp += Protocol::PAR_NUM;
	convert(list_exp, 0);
	list_exp += Protocol::ANS_END;
	assertEquals("Listing no newsgroups.", list_exp, con_output);
	tear_down();
}

void test_delete_nonexist_ng(){
	set_up();
	Result *res;
	string del_exp;
	cout << "Test delete non-existing newsgroup." << endl;
	res = mdb->delete_ng(1);
	res->printToConnection(con);
	del_exp += Protocol::ANS_DELETE_NG;
	del_exp += Protocol::ANS_NAK;
	del_exp += Protocol::ERR_NG_DOES_NOT_EXIST;
	del_exp += Protocol::ANS_END;
	assertEquals("Delete newsgroup", del_exp, con_output);
	con_output = string();
	delete res;
	tear_down();
}

void test_create_art(){
	set_up();
	Result *res;
	string exp;
	cout << "Test create single article." << endl;
	res = mdb->create_ng("test_ng1");
	delete res;
	string title("test_title");
	string author("test_author");
	string text("test_text");
	res = mdb->create_art(1, title, author, text);
	res->printToConnection(con);
	exp += Protocol::ANS_CREATE_ART;
	exp += Protocol::ANS_ACK;
	exp += Protocol::ANS_END;
	assertEquals("Create article", exp, con_output);
	delete res;
	tear_down();
}

void test_create_no_ng_art(){
	set_up();
	Result *res;
	string exp;
	cout << "Test create article without newsgroup." << endl;
	string title("test_title");
	string author("test_author");
	string text("test_text");
	res = mdb->create_art(1, title, author, text);
	res->printToConnection(con);
	exp += Protocol::ANS_CREATE_ART;
	exp += Protocol::ANS_NAK;
	exp += Protocol::ERR_NG_DOES_NOT_EXIST;
	exp += Protocol::ANS_END;
	assertEquals("Create no ng article", exp, con_output);
	delete res;
	tear_down();
}

void test_list_art(){
	set_up();
	Result *res;
	string exp;
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
	exp += Protocol::ANS_LIST_ART;
	exp += Protocol::ANS_ACK;
	exp += Protocol::PAR_NUM;
	convert(exp, 2);
	exp += Protocol::PAR_NUM;
	convert(exp, 1);
	exp += Protocol::PAR_STRING;
	convert(exp, title1);
	exp += Protocol::PAR_NUM;
	convert(exp, 2);
	exp += Protocol::PAR_STRING;
	convert(exp, title2);
	exp += Protocol::ANS_END;
	assertEquals("List article", exp, con_output);
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
	string exp;
	cout << "Test list article without newsgroup." << endl;
	string title("test_title");
	string author("test_author");
	string text("test_text");
	res = mdb->list_art(1);
	res->printToConnection(con);
	exp += Protocol::ANS_LIST_ART;
	exp += Protocol::ANS_NAK;
	exp += Protocol::ERR_NG_DOES_NOT_EXIST;
	exp += Protocol::ANS_END;
	assertEquals("List no ng article", exp, con_output);
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
}
