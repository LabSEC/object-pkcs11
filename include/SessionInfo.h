#ifndef SESSION_INFO_H
#define SESSION_INFO_H

#include <string>

#include "pkcs11.h"

namespace objck {
/*!
 *@brief <b>PKCS#11 Session Info</b><br>
 * 
 * This class is a CK_SESSION_INFO wrapper, it
 * holds the original struct protected and
 * provides public functions to return its values.
 *
 * @see Session
 * @see CK_SESSION_INFO
 *
 * @author Lucas Pandolfo Perin
 */
class SessionInfo
{
	friend class Session;
protected:
	CK_SESSION_INFO _info;
public:
	SessionInfo(CK_SESSION_INFO info);

	virtual ~SessionInfo(){};

	enum SessionFlags
	{
		EMPTY = 0,
		RW_SESSION = 2,
		SERIAL_SESSION =4,
		UNKNOWN = 32
	};

	unsigned long slotId();
	unsigned long state();
	SessionInfo::SessionFlags flags();
	unsigned long deviceError();//TODO(perin) enumerate erros later in device object
	CK_SESSION_INFO getSessionInfo();
};
}/*END NAMESPACE*/
#endif /*SESSION_INFO_H*/
