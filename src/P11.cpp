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

Info P11::getInfo()
{
	CK_INFO info;
	rv = (*functionList->C_GetInfo)(&info);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
	return info;
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
	int len = soPin.length();
	CK_ULONG pinLength = len;
	CK_UTF8CHAR* utf8SoPin = new CK_UTF8CHAR[len];
	strncpy((char*)utf8SoPin, soPin.c_str(), len);

	len = label.length();
	CK_UTF8CHAR* utf8Label = new CK_UTF8CHAR[len];
	strncpy((char*)utf8Label, label.c_str(), len);

	rv = (*functionList->C_InitToken)(slot, utf8SoPin, pinLength, utf8Label);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
}

void P11::initPin()
{
	NOT_IMPLEMENTED;
}

void P11::openSession(unsigned int slot, Session& session)
{
	rv = (*functionList->C_OpenSession)(slot, CKF_SERIAL_SESSION | CKF_RW_SESSION, 
			NULL_PTR, NULL_PTR, &session);
	if(rv)
	{
		FAILED;
		throw P11Exception(rv);
	}
	OK;
}

void P11::login()
{
	NOT_IMPLEMENTED;
}

