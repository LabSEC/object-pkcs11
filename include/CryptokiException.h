#ifndef CryptokiEXCEPTION_H
#define CryptokiEXCEPTION_H

#include "pkcs11.h"
#include <exception>

/*!
 * @brief <b>General Cryptoki API Exception</b><br>
 *
 * This is a general Exception for the API class,
 * it contains the pkcs11 base error codes and
 * returns a understandable string rather than 
 * a number.
 *
 * @see pkcs11.h
 */
class CryptokiException : public std::exception
{
public:
	/*!
	* Default Constructor.
	* @param erc PKCS#11 Error code.
	*/
	CryptokiException(CK_RV erc = CKR_GENERAL_ERROR) { _where="not specified"; _erc=erc; };

	/*!
	* Constructor with "where" message.
	* @param where String with place where exception occurred.
	* @param erc PKCS#11 Error code.
	*/
	CryptokiException(const char* where,CK_RV erc = CKR_GENERAL_ERROR) { _where=where; _erc=erc; };

	/*!
	* Default destructor.
	*/
	virtual ~CryptokiException() throw(){};

	/*!
	* Returns a string with the name of the PKCS#11error code.
	*/
	virtual const char* what() const throw()
	{
		switch(_erc)
		{
			case 666: return "Precondition failed";
			case 777: return "Object is not initialized";
			case CKR_OK: return "CKR_OK";
			case CKR_CANCEL: return "CKR_CANCEL";
			case CKR_HOST_MEMORY: return "CKR_HOST_MEMORY";
			case CKR_SLOT_ID_INVALID: return "CKR_SLOT_ID_INVALID";
			case CKR_GENERAL_ERROR: return "CKR_GENERAL_ERROR";
			case CKR_FUNCTION_FAILED: return "CKR_FUNCTION_FAILED";
			case CKR_ARGUMENTS_BAD: return "CKR_ARGUMENTS_BAD";
			case CKR_NO_EVENT: return "CKR_NO_EVENT";
			case CKR_NEED_TO_CREATE_THREADS: return "CKR_NEED_TO_CREATE_THREADS";
			case CKR_CANT_LOCK: return "CKR_CANT_LOCK";
			case CKR_ATTRIBUTE_READ_ONLY: return "CKR_ATTRIBUTE_READ_ONLY";
			case CKR_ATTRIBUTE_SENSITIVE: return "CKR_ATTRIBUTE_SENSITIVE";
			case CKR_ATTRIBUTE_TYPE_INVALID: return "CKR_ATTRIBUTE_TYPE_INVALID";
			case CKR_ATTRIBUTE_VALUE_INVALID: return "CKR_ATTRIBUTE_VALUE_INVALID";
			case CKR_DATA_INVALID: return "CKR_DATA_INVALID";
			case CKR_DATA_LEN_RANGE: return "CKR_DATA_LEN_RANGE";
			case CKR_DEVICE_ERROR: return "CKR_DEVICE_ERROR";
			case CKR_DEVICE_MEMORY: return "CKR_DEVICE_MEMORY";
			case CKR_DEVICE_REMOVED: return "CKR_DEVICE_REMOVED";
			case CKR_ENCRYPTED_DATA_INVALID: return "CKR_ENCRYPTED_DATA_INVALID";
			case CKR_ENCRYPTED_DATA_LEN_RANGE: return "CKR_ENCRYPTED_DATA_LEN_RANGE";
			case CKR_FUNCTION_CANCELED: return "CKR_FUNCTION_CANCELED";
			case CKR_FUNCTION_NOT_PARALLEL: return "CKR_FUNCTION_NOT_PARALLEL";
			case CKR_FUNCTION_NOT_SUPPORTED: return "CKR_FUNCTION_NOT_SUPPORTED";
			case CKR_KEY_HANDLE_INVALID: return "CKR_KEY_HANDLE_INVALID";
			case CKR_KEY_SIZE_RANGE: return "CKR_KEY_SIZE_RANGE";
			case CKR_KEY_TYPE_INCONSISTENT: return "CKR_KEY_TYPE_INCONSISTENT";
			case CKR_KEY_NOT_NEEDED: return "CKR_KEY_NOT_NEEDED";
			case CKR_KEY_CHANGED: return "CKR_KEY_CHANGED";
			case CKR_KEY_NEEDED: return "CKR_KEY_NEEDED";
			case CKR_KEY_INDIGESTIBLE: return "CKR_KEY_INDIGESTIBLE";
			case CKR_KEY_FUNCTION_NOT_PERMITTED: return "CKR_KEY_FUNCTION_NOT_PERMITTED";
			case CKR_KEY_NOT_WRAPPABLE: return "CKR_KEY_NOT_WRAPPABLE";
			case CKR_KEY_UNEXTRACTABLE: return "CKR_KEY_UNEXTRACTABLE";
			case CKR_MECHANISM_INVALID: return "CKR_MECHANISM_INVALID";
			case CKR_MECHANISM_PARAM_INVALID: return "CKR_MECHANISM_PARAM_INVALID";
			case CKR_OBJECT_HANDLE_INVALID: return "CKR_OBJECT_HANDLE_INVALID";
			case CKR_OPERATION_ACTIVE: return "CKR_OPERATION_ACTIVE";
			case CKR_OPERATION_NOT_INITIALIZED: return "CKR_OPERATION_NOT_INITIALIZED";
			case CKR_PIN_INCORRECT: return "CKR_PIN_INCORRECT";
			case CKR_PIN_INVALID: return "CKR_PIN_INVALID";
			case CKR_PIN_LEN_RANGE: return "CKR_PIN_LEN_RANGE";
			case CKR_PIN_EXPIRED: return "CKR_PIN_EXPIRED";
			case CKR_PIN_LOCKED: return "CKR_PIN_LOCKED";
			case CKR_SESSION_CLOSED: return "CKR_SESSION_CLOSED";
			case CKR_SESSION_COUNT: return "CKR_SESSION_COUNT";
			case CKR_SESSION_HANDLE_INVALID: return "CKR_SESSION_HANDLE_INVALID";
			case CKR_SESSION_PARALLEL_NOT_SUPPORTED: return "CKR_SESSION_PARALLEL_NOT_SUPPORTED";
			case CKR_SESSION_READ_ONLY: return "CKR_SESSION_READ_ONLY";
			case CKR_SESSION_EXISTS: return "CKR_SESSION_EXISTS";
			case CKR_SESSION_READ_ONLY_EXISTS: return "CKR_SESSION_READ_ONLY_EXISTS";
			case CKR_SESSION_READ_WRITE_SO_EXISTS: return "CKR_SESSION_READ_WRITE_SO_EXISTS";
			case CKR_SIGNATURE_INVALID: return "CKR_SIGNATURE_INVALID";
			case CKR_SIGNATURE_LEN_RANGE: return "CKR_SIGNATURE_LEN_RANGE";
			case CKR_TEMPLATE_INCOMPLETE: return "CKR_TEMPLATE_INCOMPLETE";
			case CKR_TEMPLATE_INCONSISTENT: return "CKR_TEMPLATE_INCONSISTENT";
			case CKR_TOKEN_NOT_PRESENT: return "CKR_TOKEN_NOT_PRESENT";
			case CKR_TOKEN_NOT_RECOGNIZED: return "CKR_TOKEN_NOT_RECOGNIZED";
			case CKR_TOKEN_WRITE_PROTECTED: return "CKR_TOKEN_WRITE_PROTECTED";
			case CKR_UNWRAPPING_KEY_HANDLE_INVALID: return "CKR_UNWRAPPING_KEY_HANDLE_INVALID";
			case CKR_UNWRAPPING_KEY_SIZE_RANGE: return "CKR_UNWRAPPING_KEY_SIZE_RANGE";
			case CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT: return "CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT";
			case CKR_USER_ALREADY_LOGGED_IN: return "CKR_USER_ALREADY_LOGGED_IN";
			case CKR_USER_NOT_LOGGED_IN: return "CKR_USER_NOT_LOGGED_IN";
			case CKR_USER_PIN_NOT_INITIALIZED: return "CKR_USER_PIN_NOT_INITIALIZED";
			case CKR_USER_TYPE_INVALID: return "CKR_USER_TYPE_INVALID";
			case CKR_USER_ANOTHER_ALREADY_LOGGED_IN: return "CKR_USER_ANOTHER_ALREADY_LOGGED_IN";
			case CKR_USER_TOO_MANY_TYPES: return "CKR_USER_TOO_MANY_TYPES";
			case CKR_WRAPPED_KEY_INVALID: return "CKR_WRAPPED_KEY_INVALID";
			case CKR_WRAPPED_KEY_LEN_RANGE: return "CKR_WRAPPED_KEY_LEN_RANGE";
			case CKR_WRAPPING_KEY_HANDLE_INVALID: return "CKR_WRAPPING_KEY_HANDLE_INVALID";
			case CKR_WRAPPING_KEY_SIZE_RANGE: return "CKR_WRAPPING_KEY_SIZE_RANGE";
			case CKR_WRAPPING_KEY_TYPE_INCONSISTENT: return "CKR_WRAPPING_KEY_TYPE_INCONSISTENT";
			case CKR_RANDOM_SEED_NOT_SUPPORTED: return "CKR_RANDOM_SEED_NOT_SUPPORTED";
			case CKR_RANDOM_NO_RNG: return "CKR_RANDOM_NO_RNG";
			case CKR_DOMAIN_PARAMS_INVALID: return "CKR_DOMAIN_PARAMS_INVALID";
			case CKR_BUFFER_TOO_SMALL: return "CKR_BUFFER_TOO_SMALL";
			case CKR_SAVED_STATE_INVALID: return "CKR_SAVED_STATE_INVALID";
			case CKR_INFORMATION_SENSITIVE: return "CKR_INFORMATION_SENSITIVE";
			case CKR_STATE_UNSAVEABLE: return "CKR_STATE_UNSAVEABLE";
			case CKR_CRYPTOKI_NOT_INITIALIZED: return "CKR_CRYPTOKI_NOT_INITIALIZED";
			case CKR_CRYPTOKI_ALREADY_INITIALIZED: return "CKR_CRYPTOKI_ALREADY_INITIALIZED";
			case CKR_MUTEX_BAD: return "CKR_MUTEX_BAD";
			case CKR_MUTEX_NOT_LOCKED: return "CKR_MUTEX_NOT_LOCKED";
			case CKR_FUNCTION_REJECTED: return "CKR_FUNCTION_REJECTED";
			case CKR_VENDOR_DEFINED: return "CKR_VENDOR_DEFINED";
			default: return "Unknown error";
		}
	};
	
	/*!
	* Returns a string with the place where the exception occurred.
	*/
	virtual const char* where() const throw() { return _where; };

	/*!
	* Returns the PKCS#11 error code.
	* @return CK_RV
	*/
	virtual CK_RV getErrorCode() { return _erc; };
protected:
	CK_RV _erc;
	const char* _where;
};
#endif /*CryptokiEXCEPTION_H*/
