#include <iostream>

#include "net/protocol.h"
#include "net/connectionclosedexception.h"
#include "db/create_ng_result.h"

using namespace net;
using namespace std;

namespace db {
	void CreateNGResult::printToConnection(MessageHandler &mh) throw(ConnectionClosedException) {
		mh.print_byte(Protocol::ANS_CREATE_NG);
		if (message != Protocol::ANS_ACK)
			mh.print_byte(Protocol::ANS_NAK);
		mh.print_byte(message);
		mh.print_byte(Protocol::ANS_END);
	}

	void CreateNGResult::printToCout(){
		if (message == Protocol::ANS_ACK)
			cout << "Newsgroup successfully created" << endl;
		else
			cout << "ERROR: Newsgroup already exists" << endl;
	}
}
