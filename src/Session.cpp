#include "Session.h"
namespace objck {

void Session::closeSession()
{
	if(isDisabled()) {OK; return;}	
	
	PRECONDITION(_functionList)
	CK_RV rv = (*_functionList->C_CloseSession)(_session);
	if(rv)
	{
		FAILED;
		throw CryptokiException(rv);
	}
	disable();
	OK;
}

SessionInfo Session::getSessionInfo()
{
	PRECONDITION(isEnabled())
	PRECONDITION(_functionList)
	CK_SESSION_INFO a;
	CK_RV rv = (*_functionList->C_GetSessionInfo)(_session, &a);
	SessionInfo inf(a);
    if(rv)
        {
            FAILED;
            throw CryptokiException(rv);
        }
    OK;
	return inf;
}

void Session::getOperationState()
{
	PRECONDITION(isEnabled())
	PRECONDITION(_functionList)
	NOT_IMPLEMENTED;
}

void Session::setOperationState()
{
	PRECONDITION(isEnabled())
	PRECONDITION(_functionList)
	NOT_IMPLEMENTED;
}

void Session::userLogin(std::string& userPin)
{
	PRECONDITION(isEnabled())
	PRECONDITION(_functionList)
	
    CK_ULONG pinLen = userPin.length();

    CK_RV rv = (*_functionList->C_Login)(_session, CKU_USER, (unsigned char*)userPin.c_str(), pinLen);
    if(rv)
    {
        FAILED;
        throw CryptokiException(rv);
    }
    OK;
}

void Session::initPin(std::string& pin)
{
	PRECONDITION(_functionList)
	NOT_IMPLEMENTED;
/*	CK_ULONG pinLen = pin.length();
	CK_UTF8CHAR* utf8pin = new CK_UTF8CHAR[pin.length()];
    strncpy((char*)utf8pin, pin.c_str(), pin.length());

    CK_RV rv = (*_functionList->C_InitPIN)(session, utf8pin, pinLen);
    if(rv)
        {
            FAILED;
            throw CryptokiException(rv);
        }
    OK;*/
}

}/*END NAMESPACE*/
