#include "CryptokiSessionInfo.h"

unsigned long CryptokiSessionInfo::slotId()
{
	return _info.slotID;
}

unsigned long CryptokiSessionInfo::state()
{
	return _info.state;
}

CryptokiSessionInfo::CryptokiSessionFlags CryptokiSessionInfo::flags()
{
	int fl = (int)_info.flags;
	if(fl < 1)
	{
		return CryptokiSessionFlags::EMPTY;
	}else if(fl > 7)
	{
		return CryptokiSessionFlags::UNKNOWN;
	}
	return static_cast<CryptokiSessionFlags>(fl);
}

unsigned long CryptokiSessionInfo::deviceError()
{
	return _info.ulDeviceError;
}

CK_SESSION_INFO CryptokiSessionInfo::getSessionInfo()
{
	return _info;
}
