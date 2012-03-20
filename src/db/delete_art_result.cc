#include "db/delete_art_result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"
#include "net/protocol.h"

using namespace net;

namespace db {
	void DeleteArtResult::printToConnection(net::Connection &conn) throw(net::ConnectionClosedException) {
		conn.write(Protocol::ANS_DELETE_ART);		
		if(message != Protocol::ANS_ACK)
			conn.write(Protocol::ANS_NAK);
		conn.write(message);
		conn.write(Protocol::ANS_END);
	}

	void DeleteArtResult::printToCout() {
		; // TODO
	}
}

