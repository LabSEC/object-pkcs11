#include "P11.h"

P11::P11(std::string& path)
{
//TODO(perin): check if module was loaded correctly.
	functionList = 0;
	loadModule(path);
	loadFunctions();
}

P11::~P11()
{
	if(this->module)
	{
		TRACE("Cleaning up module.");
		dlclose(module);
	}
}

void P11::loadModule(std::string& path)
{
	//TODO(perin): check if module is already loaded;
	TRACE("Loading module from PATH");
	this->module = dlopen(path.c_str(), RTLD_LAZY);
}

void P11::loadFunctions()
{
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(module, "C_GetFunctionList");
	rv = getFuncList(&functionList);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
}

void P11::initialize()
{
	rv = (*functionList->C_Initialize)(0);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
}

void P11::finalize()
{
	(*functionList->C_Finalize)(0);
	OK;
}

CryptokiInfo P11::getInfo()
{
	CryptokiInfo cryptokiInfo;
	rv = (*functionList->C_GetInfo)(cryptokiInfo.getInfo());
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
	return cryptokiInfo;
}

FunctionList P11::getFunctionList()
{
	CK_FUNCTION_LIST_PTR fList;
	rv = (*functionList->C_GetFunctionList)(&fList);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
	return *fList;
}

//TODO(perin): copy strings without casting. CK_UTF8CHAR is unsigned char.
void P11::initToken(unsigned int slot, std::string& soPin, std::string& label)
{
	CK_ULONG soPinLen = soPin.length();
	CK_UTF8CHAR* utf8soPin = new CK_UTF8CHAR[soPin.length()];
	strncpy((char*)utf8soPin, soPin.c_str(), soPin.length());

	CK_UTF8CHAR* utf8label = new CK_UTF8CHAR[label.length()];
	strncpy((char*)utf8label, label.c_str(), label.length());

	rv = (*functionList->C_InitToken)(slot, utf8soPin, soPinLen, utf8label);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
}

void P11::initPin(Session& session, std::string& pin)
{
	CK_ULONG pinLen = pin.length();
	CK_UTF8CHAR* utf8pin = new CK_UTF8CHAR[pin.length()];
    strncpy((char*)utf8pin, pin.c_str(), pin.length());

    rv = (*functionList->C_InitPIN)(session, utf8pin, pinLen);
    if(rv)
        {
            FAILED;
            throw P11Exception(rv);
        }
    OK;
}

void P11::openSession(unsigned int slot, Session& session)
{
    //TODO(perin): Here we could use flgs/enum to set Session settings.
    rv = (*functionList->C_OpenSession)(slot, CKF_SERIAL_SESSION | CKF_RW_SESSION,
                                        NULL_PTR, NULL_PTR, &session);
    if(rv)
        {
            FAILED;
            throw P11Exception(rv);
        }
    OK;
}

void P11::login(Session& session, std::string& soPin)
{
    CK_ULONG pinLen = soPin.length();
    CK_UTF8CHAR* utf8soPin = new CK_UTF8CHAR[soPin.length()];
    strncpy((char*)utf8soPin, soPin.c_str(), soPin.length());

    rv = (*functionList->C_Login)(session, CKU_SO, utf8soPin, pinLen);
    if(rv)
        {
            FAILED;
            throw P11Exception(rv);
        }
    OK;
}
