#include <iostream>
#include "db/create_art_result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"
#include "net/protocol.h"

using namespace net;
using namespace std;

namespace db {

	void CreateArtResult::printToConnection(MessageHandler &mh) throw(ConnectionClosedException) {
		mh.print_byte(Protocol::ANS_CREATE_ART);
		if(message != Protocol::ANS_ACK) {
			mh.print_byte(Protocol::ANS_NAK);
		}
		mh.print_byte(message);
		mh.print_byte(Protocol::ANS_END);
	}

	void CreateArtResult::toString(ostream &out) const {
		if (message == Protocol::ANS_ACK) {
			out << "Article successfully created" << endl;
		} else {
			out << "ERROR: Article already exists" << endl;
		}
	}
}
