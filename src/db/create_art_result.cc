#include "db/create_art_result.h"
#include "net/connectionclosedexception.h"
#include "net/connection.h"

using namespace net;

namespace db {
	void CreateArtResult::printToConnection(Connection &conn) throw(ConnectionClosedException) {
		conn.write(Protocol::ANS_CREATE_ART);		
		if (message != Protocol::ANS_ACK)
			conn.write(Protocol::ANS_NAK);
		conn.write(message);
		conn.write(Protocol::ANS_END);
	}
}
