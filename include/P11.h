#ifndef P11_H
#define P11_H

#include <assert.h>
#include <string>
#include <cstring>
#include <dlfcn.h>

#include "pkcs11.h"
#include "P11Exception.h"
#include "macros.h"
#include "CryptokiInfo.h"

typedef CK_FUNCTION_LIST FunctionList;
typedef CK_SESSION_HANDLE Session;

/*!
 * @brief <b>P11 API</b><br>
 *
 * This class calls pkcs11 functions from pkcs11
 * module. The module is loaded dynamically and
 * functions are called through CK_FUNCTION_LIST.<p>
 *
 * <b> Module must implement 'C_GetFunctionList' </b><p>
 *
 * @see pkcs11.h
 * @see P11Exception.h
 *
 * @author Lucas Pandolfo Perin
 */
class P11
{
protected:
	void* module; 
	CK_RV rv;
	CK_FUNCTION_LIST_PTR functionList;
	
	/*!
 	* Protected function that loads
 	* the pkcs11 module usinf libdl, dynamically.
 	*/ 
	void loadModule(std::string& path);

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
public:

	P11(std::string& path);

	virtual ~P11();

	/*! @addtogroup general
	*  General Purpose functions
	* @{
	*/
	
	/*!
	* Initializes Cryptoki.
	*/
	void initialize();

	/*!
	* Clean up miscellaneous Cryptoki associated resources.
	*/
	void finalize();

	/*!
	* Obtains general information about Cryptoki.
	*/
	CryptokiInfo getInfo();
	
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

	/*!
	* Initializes the normal user's PIN.
	*/
	void initPin(Session& session, std::string& pin);

	/*! @} 
	* @addtogroup session
	*  Session maagement functions.
	* @{
	*/

	/*!
	* opens a connection between an application and a 
	* particular token or sets up an application callback 
	* for token insertion.
	*/
	void openSession(unsigned int slot, Session& session);

	/*!
	* Logs into a Token.
	*/
	void login(Session& session, std::string& soPin);

	/*! @} */
};
#endif /*P11_h*/
