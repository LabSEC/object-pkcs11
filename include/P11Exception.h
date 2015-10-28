#ifndef P11EXCEPTION_H
#define P11EXCEPTION_H

#include "pkcs11.h"
#include <exception>

/*!
 * @brief <b>General P11 API Exception</b><br>
 *
 * This is a general Exception for the API class,
 * it contains the pkcs11 base error codes and
 * returns a understandable string rather than 
 * a number.
 *
 * @see pkcs11.h
 */
class P11Exception : public std::exception
{
public:
	P11Exception(CK_RV erc = CKR_GENERAL_ERROR);
	virtual ~P11Exception() throw(){};
	virtual const char* what() const throw();
	virtual CK_RV getErrorCode();
protected:
	CK_RV erc;
};
#endif /*P11EXCEPTION_H*/
