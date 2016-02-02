#include "Cryptoki.h"

namespace objck {

Cryptoki::Cryptoki(const std::string& path) : _module(0), _functionList(0)
{
//TODO(perin): check if module was loaded correctly.
	loadModule(path);
	loadFunctions();
}

Cryptoki::~Cryptoki()
{
	if(_module)
	{
		TRACE("Cleaning up module.");
		finalize();
		dlclose(_module);
	}
}

void Cryptoki::loadModule(const std::string& path)
{
	//TODO(perin): check if module is already loaded;
	TRACE("Loading module from PATH");
	_module = dlopen(path.c_str(), RTLD_LAZY);
	if (!_module) {
		TRACE(dlerror());
		FAILED;
	}
}

void Cryptoki::loadFunctions()
{
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(_module, "C_GetFunctionList");
	CK_RV rv  = getFuncList(&_functionList);
	if(rv)
	{
		FAILED;
		throw CryptokiException(rv);
	}
	OK;
}

void Cryptoki::initialize()
{
	PRECONDITION(_functionList)
	CK_RV rv  = (*_functionList->C_Initialize)(0);
	if(rv)
	{
		FAILED;
		throw CryptokiException(rv);
	}
	OK;
}

void Cryptoki::finalize()
{
	PRECONDITION(_functionList)
	(*_functionList->C_Finalize)(0);
	OK;
}

Info Cryptoki::getInfo()
{
	PRECONDITION(_functionList)
	Info cryptokiInfo;
	CK_RV rv  = (*_functionList->C_GetInfo)(&cryptokiInfo._info);
	if(rv)
	{
		FAILED;
		throw CryptokiException(rv);
	}
	OK;
	return cryptokiInfo;
}

FunctionList Cryptoki::getFunctionList()
{
	PRECONDITION(_functionList)
	CK_FUNCTION_LIST_PTR fListPtr;
	
	CK_RV rv  = (*_functionList->C_GetFunctionList)(&fListPtr);
	if(rv)
	{
		FAILED;
		throw CryptokiException(rv);
	}
	OK;
	//CK_FUNCTION_LIST fList = *fListPtr;
	//return fList;
	return *fListPtr;
}

//TODO(perin): copy strings without casting. CK_UTF8CHAR is unsigned char.
void Cryptoki::initToken(unsigned int slot, std::string& soPin, std::string& label)
{
	PRECONDITION(_functionList)
	CK_ULONG soPinLen = soPin.length();
	CK_UTF8CHAR* utf8soPin = new CK_UTF8CHAR[soPin.length()];
	strncpy((char*)utf8soPin, soPin.c_str(), soPin.length());

	CK_UTF8CHAR* utf8label = new CK_UTF8CHAR[label.length()];
	strncpy((char*)utf8label, label.c_str(), label.length());

	CK_RV rv  = (*_functionList->C_InitToken)(slot, utf8soPin, soPinLen, utf8label);
	if(rv)
	{
		FAILED;
		throw CryptokiException(rv);
	}
	OK;
}

Session Cryptoki::openSession(unsigned int slot,
	SessionInfo::SessionFlags flags,
	CryptokiNotify* notify, void* appPtr)
{
	PRECONDITION(_functionList)
	Session sn;
	//TODO(Perin): Implement notify callbacks
    CK_RV rv  = (*_functionList->C_OpenSession)(slot, flags, 0, 0, &sn._session);
    if(rv)
        {
            FAILED;
            throw CryptokiException(rv);
        }
    OK;
	sn._functionList = _functionList;
	sn.enable();
	return sn;
}

void Cryptoki::closeAllSessions(unsigned int slot)
{
	PRECONDITION(_functionList)
	CK_RV rv  = (_functionList->C_CloseAllSessions)(slot);
    if(rv)
        {
            FAILED;
            throw CryptokiException(rv);
        }
    OK;
}

}/*END NAMESPACE*/
