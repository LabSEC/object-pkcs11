#ifndef P11_H
#define P11_H

#include <assert.h>
#include <string>
#include <cstring>
//#include <stdlib.h>
//#include <stdio.h>
#include <dlfcn.h>

#include "pkcs11.h"
#include "P11Exception.h"
#include "macros.h"

typedef CK_INFO Info;
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
 */
class P11
{

	void* module; 
	CK_RV rv;
	CK_FUNCTION_LIST_PTR functionList;

	void loadModule(std::string& path);

	void closeModule();

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
