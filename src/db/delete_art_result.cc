#include <iostream>

#include "db/delete_art_result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"
#include "net/protocol.h"

using namespace net;
using namespace std;

namespace db {
	void DeleteArtResult::printToConnection(MessageHandler &mh) throw(net::ConnectionClosedException) {
		mh.print_byte(Protocol::ANS_DELETE_ART);
		if(message != Protocol::ANS_ACK)
			mh.print_byte(Protocol::ANS_NAK);
		mh.print_byte(message);
		mh.print_byte(Protocol::ANS_END);
	}

	void DeleteArtResult::printToCout() {
		if (message == Protocol::ANS_ACK)
			cout << "Article successfully deleted" << endl;
		else if(message == Protocol::ERR_ART_DOES_NOT_EXIST)
			cout << "ERROR: Article doesn't exist" << endl;
		else
			cout << "ERROR: Newsgroup doesn't exist" << endl;
	}
}

