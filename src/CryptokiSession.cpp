#include "CryptokiSession.h"


void CryptokiSession::closeSession()
{
	NOT_IMPLEMENTED;
}

CryptokiSessionInfo CryptokiSession::getSessionInfo()
{
	CryptokiSessionInfo inf;
	NOT_IMPLEMENTED;
	return inf;
}

void CryptokiSession::getOperationState()
{
	NOT_IMPLEMENTED;
}

void CryptokiSession::setOperationState()
{
	NOT_IMPLEMENTED;
}

void CryptokiSession::login(std::string& soPin)
{
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
