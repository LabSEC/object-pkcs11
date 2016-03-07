#ifndef SESSION_H
#define SESSION_H

#include "Stateful.h"
#include "pkcs11.h"
#include "macros.h"
#include "CryptokiException.h"
#include "SessionInfo.h"

namespace objck {
/*!
 * @brief <b>PKCS#11 Sessions</b><br>
 *
 * This class is a CK_SESSION_HANDLE wrapper,
 * it holds the session handle, enumerated flags
 * and all PKCS#11 session functions related to
 * session. Session should be created through
 * P11::openSession.
 *
 * @see pkcs11.h
 * @see CK_SESSION_HANDLE
 * @see Cryptoki.h
 *
 * @author Lucas Pandolfo Perin
 */
class Session : public Stateful
{
	friend class Cryptoki;

protected:
	CK_SESSION_HANDLE _session;
	CK_FUNCTION_LIST_PTR _functionList;
public:
	Session() : Stateful(), _functionList(0) {};
	Session(Session&& other) {
		_session = std::move(other._session);	
		_functionList = std::move(other._functionList);	
		_currentState = other._currentState;
		other._currentState = DISABLED;
	};
	virtual ~Session(){ try{closeSession();}catch(...){} _functionList = 0;};
	Session& operator=(const Session& other) = delete;
	Session& operator=(Session&& other)
	{
		_session = std::move(other._session);	
		_functionList = std::move(other._functionList);	
		_currentState = other._currentState;
		other._currentState = DISABLED;
		return *this;
	};

	/*!
	* @addtogroup session
	* Session management functions
	* @{
	*/
	SessionInfo getSessionInfo();
	void getOperationState();
	void setOperationState();
	void closeSession();
	
	/*!
	* Initializes the normal user's PIN.
	*/
	void initPin(std::string& pin);

	
	/*!
	* Logs into a Token as a user.
	*/
	void userLogin(std::string& soPin);

	CK_SESSION_HANDLE getSessionHandle();
	void logout();
	/*! @} */
};
}/*END NAMESPACE*/
#endif /*SESSION_H*/
