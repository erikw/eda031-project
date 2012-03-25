#include <string>
#include <iostream>

#include "db/delete_ng_result.h"
#include "net/connectionclosedexception.h"
#include "net/protocol.h"
#include "net/connection.h"


using namespace net;
using namespace std;

namespace db {
	void DeleteNGResult::printToConnection(MessageHandler &mh) throw (ConnectionClosedException) {
		mh.print_byte(Protocol::ANS_DELETE_NG);
		if(message!=Protocol::ANS_ACK)
			mh.print_byte(Protocol::ANS_NAK);
		mh.print_byte(message);
		mh.print_byte(Protocol::ANS_END);
	}

	void DeleteNGResult::toString(ostream &out) const {
		if (message == Protocol::ANS_ACK){
			out << "Newsgroup successfully deleted" << endl;
		} else {
			out << "ERROR: Newsgroup doesn't exist" << endl;
		}
	}
}
