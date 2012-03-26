#include "db/get_art_result.h"

#include <iostream>

#include "net/connectionclosedexception.h"
#include "net/protocol.h"

namespace db {
	using namespace net;
	using namespace std;

	void GetArtResult::printToConnection(MessageHandler &mh) throw(net::ConnectionClosedException) {
		mh.print_byte(Protocol::ANS_GET_ART);
		if (message != Protocol::ANS_ACK){
			mh.print_byte(Protocol::ANS_NAK);
			mh.print_byte(message);
		} else {
			mh.print_byte(Protocol::ANS_ACK);
			mh.print_string(title);
			mh.print_string(author);
			mh.print_string(text);
		}
		mh.print_byte(Protocol::ANS_END);
	}

	void GetArtResult::toString(ostream &out) const {
		if (message == Protocol::ANS_ACK){
			out << title << "\tFrom: " << author << endl;
			out << text << endl;
		} else if(message == Protocol::ERR_ART_DOES_NOT_EXIST) {
			out << "ERROR: Article doesn't exist" << endl;
		} else {
			out << "ERROR: News group doesn't exist" << endl;
		}
	}
}
