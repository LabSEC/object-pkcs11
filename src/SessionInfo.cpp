#include "SessionInfo.h"
namespace objck {

unsigned long SessionInfo::slotId() {
	return _info.slotID;
}

unsigned long SessionInfo::state() {
	return _info.state;
}

SessionInfo::SessionFlags SessionInfo::flags() {
	int fl = (int)_info.flags;
	if(fl < 1) {
		return SessionFlags::EMPTY;
	} else if(fl > 7) {
		return SessionFlags::UNKNOWN;
	}
	return static_cast<SessionFlags>(fl);
}

unsigned long SessionInfo::deviceError() {
	return _info.ulDeviceError;
}

CK_SESSION_INFO SessionInfo::getSessionInfo() {
	return _info;
}

}/*END NAMESPACE*/
