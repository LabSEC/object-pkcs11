#ifndef CRYPTOKI_H
#define CRYPTOKI_H

#include <string>
#include <cstring>
#include <dlfcn.h>

#include "pkcs11.h"
#include "CryptokiException.h"
#include "macros.h"
#include "Info.h"
#include "Session.h"
#include "SessionInfo.h"

typedef CK_FUNCTION_LIST FunctionList;
typedef CK_NOTIFY CryptokiNotify;

namespace objck {
/*!
 * @brief <b>Cryptoki API</b><br>
 *
 * This class calls pkcs11 functions from pkcs11
 * module. The module is loaded dynamically and
 * functions are called through CK_FUNCTION_LIST.<p>
 *
 * <b> Module must implement 'C_GetFunctionList' </b><p>
 *
 * @see pkcs11.h
 * @see CryptokiException.h
 *
 * @author Lucas Pandolfo Perin
 */
class Cryptoki
{
protected:
	void* _module; 
	CK_FUNCTION_LIST_PTR _functionList;
	CK_RV _rv;
	
	/*!
 	* Protected function that loads
 	* the pkcs11 module usinf libdl, dynamically.
 	*/ 
	void loadModule(const std::string& path);

	/*!
 	* Protected function that unloads
 	* the pkcs11 module from libdl.
 	*/
	void closeModule();

	/*!
 	* Protected funtion that loads all the
 	* PKCS#11 functions using C_GetFunctionList.
 	* The PKCS#11 module must implement this
 	* function in order for this API to work.
 	*/
	void loadFunctions();
	
	/*!
	* Clean up miscellaneous Cryptoki associated resources.
	*/
	void finalize();

public:

	Cryptoki(const std::string& path);

	virtual ~Cryptoki();

	/*! @addtogroup general
	*  General Purpose functions
	* @{
	*/
	
	/*!
	* Initializes Cryptoki.
	*/
	void initialize();

	/*!
	* Obtains general information about Cryptoki.
	*/
	Info getInfo();
	
	/*!
	* Obtains entry points of Cryptoki library functions.
	*/
	FunctionList getFunctionList();

	/*! @} 
	* @addtogroup slot&token
	*  Slot and Token anagement functions
	* @{
	*/

	/*!
	* Initializes a Token.
	*/
	void initToken(unsigned int slot, std::string& soPin, std::string& label);

	/*! @} 
	* @addtogroup session
	*  Session maagement functions.
	* @{
	*/

	/*!
	* Opens a connection between an application and a 
	* particular token or sets up an application callback 
	* for token insertion.
	*
	* @param slot Specifies the token slot..
	* @param flags Flags to determine if conection is R/RW
	* (SERIAL_SESSION must always be set to true).
	* @param notify Address of the notification callback function.
	* @param appPtr Application defined pointer to be passed to 
	* the notification callback.
	*
	* @return Session
	* @throw CryptokiException
	*/
	Session openSession(unsigned int slot, 
		SessionInfo::SessionFlags flags = SessionInfo::SERIAL_SESSION,
		CryptokiNotify* notify = 0, void* appPtr = 0);

	/*!
	* Closes all sessions an aplicarion has with a token.
	*
	* @param slot Specifies the token slot.
	*
	* @throw CryptokiException
	*/
	void closeAllSessions(unsigned int slot);
	
	/*! @} */
};
}/*END NAMESPACE*/
#endif /*CRYPTOKI_H*/
