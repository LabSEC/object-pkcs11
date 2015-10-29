#include "P11.h"

P11::P11(std::string& path)
{
//TODO(perin): check if module was loaded correctly.
	_functionList = 0;
	loadModule(path);
	loadFunctions();
}

P11::~P11()
{
	if(_module)
	{
		TRACE("Cleaning up module.");
		dlclose(_module);
	}
}

void P11::loadModule(std::string& path)
{
	//TODO(perin): check if module is already loaded;
	TRACE("Loading module from PATH");
	_module = dlopen(path.c_str(), RTLD_LAZY);
}

void P11::loadFunctions()
{
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(_module, "C_GetFunctionList");
	_rv = getFuncList(&_functionList);
	if(_rv)
	{
		FAILED;
		throw P11Exception(_rv);
	}
	OK;
}

void P11::initialize()
{
	PRECONDITION(_functionList)
	_rv = (*_functionList->C_Initialize)(0);
	if(_rv)
	{
		FAILED;
		throw P11Exception(_rv);
	}
	OK;
}

void P11::finalize()
{
	PRECONDITION(_functionList)
	(*_functionList->C_Finalize)(0);
	OK;
}

CryptokiInfo P11::getInfo()
{
	PRECONDITION(_functionList)
	CryptokiInfo cryptokiInfo;
	_rv = (*_functionList->C_GetInfo)(&cryptokiInfo._info);
	if(_rv)
	{
		FAILED;
		throw P11Exception(_rv);
	}
	OK;
	cryptokiInfo.ress();
	return cryptokiInfo;
}

FunctionList P11::getFunctionList()
{
	PRECONDITION(_functionList)
	CK_FUNCTION_LIST_PTR fList;
	_rv = (*_functionList->C_GetFunctionList)(&fList);
	if(_rv)
	{
		FAILED;
		throw P11Exception(_rv);
	}
	OK;
	return *fList;
}

//TODO(perin): copy strings without casting. CK_UTF8CHAR is unsigned char.
void P11::initToken(unsigned int slot, std::string& soPin, std::string& label)
{
	PRECONDITION(_functionList)
	CK_ULONG soPinLen = soPin.length();
	CK_UTF8CHAR* utf8soPin = new CK_UTF8CHAR[soPin.length()];
	strncpy((char*)utf8soPin, soPin.c_str(), soPin.length());

	CK_UTF8CHAR* utf8label = new CK_UTF8CHAR[label.length()];
	strncpy((char*)utf8label, label.c_str(), label.length());

	_rv = (*_functionList->C_InitToken)(slot, utf8soPin, soPinLen, utf8label);
	if(_rv)
	{
		FAILED;
		throw P11Exception(_rv);
	}
	OK;
}

void P11::initPin(CryptokiSession& session, std::string& pin)
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

CryptokiSession P11::openSession(unsigned int slot,
	CryptokiSessionInfo::CryptokiSessionFlags flags,
	CryptokiNotify* notify, void* appPtr)
{
	PRECONDITION(_functionList)
	CryptokiSession sn;
	//TODO(Perin): Implement notify callbacks
    _rv = (*_functionList->C_OpenSession)(slot, flags, 0, 0, &sn._session);
    if(_rv)
        {
            FAILED;
            throw P11Exception(_rv);
        }
    OK;
	sn.ress();
	return sn;
}

void P11::closeAllSessions(unsigned int slot)
{
	PRECONDITION(_functionList)
	_rv = (_functionList->C_CloseAllSessions)(slot);
    if(_rv)
        {
            FAILED;
            throw P11Exception(_rv);
        }
    OK;
}
