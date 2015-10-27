#ifndef MAIN_CPP
#define MAIN_CPP

#include <assert.h>
#include <pkcs11.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

// Slots
#define SLOT_INVALID 9999
#define SLOT_INIT_TOKEN 0
#define SLOT_NO_INIT_TOKEN 1

// PIN
#define SLOT_0_SO1_PIN "123456"
#define SLOT_0_SO2_PIN "123456"
#define SLOT_0_USER1_PIN "123456"
#define SLOT_0_USER2_PIN "123456"

int main ( int argc, const char* argv[] )
{
	printf("Hello World\n");

	//for( int i = 0; i < argc; i++ )
	//{
	//	printf( "arg %d: %s\n", i, argv[i] );
	//}
	CK_RV rv;
	//CK_UTF8CHAR pin[] = SLOT_0_USER1_PIN;
	//CK_ULONG pinLength = sizeof(pin) - 1;
	//CK_UTF8CHAR sopin[] = SLOT_0_SO1_PIN;
	//CK_ULONG sopinLength = sizeof(sopin) - 1;
	//CK_SESSION_HANDLE hSession;

	//CK_UTF8CHAR label[32];
	//memset(label, ' ', 32);
	//memcpy(label, "token1", strlen("token1"));

	void* sym = dlopen("/usr/lib64/libsofthsm2.so", RTLD_LAZY);
	//void* sym = dlopen("/usr/lib64/opensc-pkcs11.so", RTLD_LAZY);

	assert(sym != 0);
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(sym, "C_GetFunctionList");


	CK_FUNCTION_LIST_PTR listPointer = 0;
	rv = getFuncList(&listPointer);
	assert(rv == 0);
	printf("getFuncList return: (%lu)\n", rv);

	CK_C_Initialize init = listPointer->C_Initialize;
	// (Re)initialize the token
	rv = (*init)(0);
	printf("Initializing (%lu)\n", rv);



	dlclose(sym);	
}

#endif /*MAIN_CPP*/
