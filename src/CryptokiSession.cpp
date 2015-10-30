#include "CryptokiSession.h"


void CryptokiSession::closeSession()
{
	PRECONDITION(isAlive())
	PRECONDITION(_functionList)
	_rv = (*_functionList->C_CloseSession)(_session);
    if(_rv)
        {
            FAILED;
            throw P11Exception(_rv);
        }
    OK;
	kill();
}

CryptokiSessionInfo CryptokiSession::getSessionInfo()
{
	PRECONDITION(isAlive())
	PRECONDITION(_functionList)
	CryptokiSessionInfo inf;
	CK_SESSION_INFO a;
	_rv = (*_functionList->C_GetSessionInfo)(_session, &a);
    if(_rv)
        {
            FAILED;
            throw P11Exception(_rv);
        }
    OK;
	return inf;
}

void CryptokiSession::getOperationState()
{
	PRECONDITION(isAlive())
	PRECONDITION(_functionList)
	NOT_IMPLEMENTED;
}

void CryptokiSession::setOperationState()
{
	PRECONDITION(isAlive())
	PRECONDITION(_functionList)
	NOT_IMPLEMENTED;
}

void CryptokiSession::login(std::string& soPin)
{
	PRECONDITION(isAlive())
	PRECONDITION(_functionList)
    //TODO FIX 
    NOT_IMPLEMENTED;
	/*CK_ULONG pinLen = soPin.length();
    CK_UTF8CHAR* utf8soPin = new CK_UTF8CHAR[soPin.length()];
    strncpy((char*)utf8soPin, soPin.c_str(), soPin.length());

    rv = (*functionList->C_Login)(session, CKU_SO, utf8soPin, pinLen);
    if(rv)
        {
            FAILED;
            throw P11Exception(rv);
        }
    OK;*/
}

void CryptokiSession::initPin(std::string& pin)
{
	PRECONDITION(_functionList)
	NOT_IMPLEMENTED;
/*	CK_ULONG pinLen = pin.length();
	CK_UTF8CHAR* utf8pin = new CK_UTF8CHAR[pin.length()];
    strncpy((char*)utf8pin, pin.c_str(), pin.length());

    _rv = (*_functionList->C_InitPIN)(session, utf8pin, pinLen);
    if(_rv)
        {
            FAILED;
            throw P11Exception(_rv);
        }
    OK;*/
}

