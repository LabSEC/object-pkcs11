#ifndef MAIN_CPP
#define MAIN_CPP

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <regex>
#include <string>


#include "pkcs11.h"
#include "macros.h"

// Slots
#define SLOT_INVALID 9999
#define SLOT_INIT_TOKEN 0
#define SLOT_NO_INIT_TOKEN 1

// PIN
#define SLOT_0_SO1_PIN "123456"
#define SLOT_0_SO2_PIN "123456"
#define SLOT_0_USER1_PIN "123456"
#define SLOT_0_USER2_PIN "123456"


typedef std::string string;

void* loadDefaultModule()
{
	//TODO(perin): check for loading errors.
	TRACE("Loading default module (libsofthsm2)");
	return dlopen("/usr/lib64/libsofthsm2.so", RTLD_LAZY);
}

void* loadModule(string path)
{
	//TODO(perin): check for loading errors.	
	TRACE("Loading module from PATH");
	return dlopen(path.c_str(), RTLD_LAZY);
}

int main(int argc, const char* argv[])
{

	void* sym = 0;
	if (argv[1] != 0)
	{
		std::string path = argv[1];
		sym = loadModule(path);
	}
	else
	{
		sym = loadDefaultModule();
	}
	
	CK_RV rv;

	assert(sym != 0);
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(sym, "C_GetFunctionList");


	CK_FUNCTION_LIST_PTR lp = 0;
	rv = getFuncList(&lp);
	CK_FUNCTION_LIST listPointer = *lp;
	assert(rv == CKR_OK);
	TRACE("GetFunctionList::Ok!");

	rv = listPointer.C_Initialize(0);
	assert(rv == CKR_OK);
	TRACE("Initialize::Ok!");


	//CK_UTF8CHAR pin[] = SLOT_0_USER1_PIN;
	//CK_ULONG pinLength = sizeof(pin) - 1;
	//CK_UTF8CHAR sopin[] = SLOT_0_SO1_PIN;
	//CK_ULONG sopinLength = sizeof(sopin) - 1;
	//CK_SESSION_HANDLE hSession;

	//CK_UTF8CHAR label[32];
	//memset(label, ' ', 32);
	//memcpy(label, "token1", strlen("token1"));

	dlclose(sym);	
}

#endif /*MAIN_CPP*/
