
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

template<typename T>
void assertEquals(const string& if_neq, const T& expected, const T& value) {
	if(expected != value){
		cout << if_neq << endl;
		cout << "Was [" << value << "] but expected [" << expected << "]." << endl;
	}
}

void convert(string& out, unsigned int num){
	out += (num << 24) & 0xFF;
	out += (num << 16) & 0xFF;
	out += (num << 8) & 0xFF;
	out += num & 0xFF;
}

void convert(string& out, string str){
	convert(out, str.size());
	out += str;
}

int main() {
	MemoryDB mdb;
	MockConnection con;

	cout << "Test create newsgroup" << endl;
	Result *res = mdb.create_ng("test_ng1");
	res->printToConnection(con);
	string exp;
	exp += Protocol::ANS_CREATE_NG;
	exp += Protocol::ANS_ACK;
	exp += Protocol::ANS_END;
	assertEquals("Incorrect result when creating new newsgroup.", exp, con_output);
	delete res;
	con_output = string();
	exp = string();

	cout << "Test create existing newsgroup" << endl;
	res = mdb.create_ng("test_ng1");
	res->printToConnection(con);
	exp += Protocol::ANS_CREATE_NG;
	exp += Protocol::ANS_NAK;
	exp += Protocol::ERR_NG_ALREADY_EXISTS;
	exp += Protocol::ANS_END;
	assertEquals("Incorrect result when creating existing newsgroup.",
			exp, con_output);
	delete res;
	con_output = string();
	exp = string();

	cout << "Test list existing newsgroups" << endl;
	res = mdb.create_ng("test_ng2");
	delete res;
	res = mdb.list_ng();
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
	con_output = string();
	exp = string();
}
