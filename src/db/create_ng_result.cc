#include "net/protocol.h"
#include "net/connectionclosedexception.h"
#include "db/create_ng_result.h"

using namespace net;
using namespace std;

namespace db {
	void CreateNGResult::printToConnection(Connection &conn) throw(ConnectionClosedException) {
		conn.write(Protocol::ANS_CREATE_NG);
		if (message != Protocol::ANS_ACK)
			conn.write(Protocol::ANS_NAK);
		conn.write(message);
		conn.write(Protocol::ANS_END);
	}
}
