#ifndef CRYPTOKISESSION_H
#define CRYPTOKISESSION_H

#include "P11Init.h"
#include "pkcs11.h"
#include "macros.h"
#include "P11Exception.h"
#include "CryptokiSessionInfo.h"

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
 * @see P11.h
 *
 * @author Lucas Pandolfo Perin
 */
class CryptokiSession : public P11Init
{
	friend class P11;

protected:
	CK_SESSION_HANDLE session;
	CK_RV rv;
	CK_FUNCTION_LIST_PTR functionList;
	
public:
	CryptokiSession() : P11Init() {};
	virtual ~CryptokiSession(){};

	/*!
	* @addtogroup session
	* Session management functions
	* @{
	*/
	void closeSession();
	CryptokiSessionInfo getSessionInfo();
	void getOperationState();
	void setOperationState();
	
	/*!
	* Logs into a Token.
	*/
	void login(std::string& soPin);
	
	CK_SESSION_HANDLE getSessionHandle();
	void logout();
	/*! @} */
};
#endif /*CRYPTOKISESSION_H*/
