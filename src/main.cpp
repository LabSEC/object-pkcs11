#include <assert.h>
#include <cryptoki.h>
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

	void* sym = dlopen("/usr/lib64/libsofthsm2.so", RTLD_LAZY);
	assert(sym != 0);
	CK_C_GetFunctionList gfl = (CK_C_GetFunctionList) dlsym(sym, "C_GetFunctionList");

	CK_RV rv;
	CK_UTF8CHAR pin[] = SLOT_0_USER1_PIN;
	CK_ULONG pinLength = sizeof(pin) - 1;
	CK_UTF8CHAR sopin[] = SLOT_0_SO1_PIN;
	CK_ULONG sopinLength = sizeof(sopin) - 1;
	CK_SESSION_HANDLE hSession;

	CK_UTF8CHAR label[32];
	memset(label, ' ', 32);
	memcpy(label, "token1", strlen("token1"));

	//TODO: Carregar o C_GetFunctionList via Libdl,
	//usar funcoes carregadas a partir dele.
	CK_FUNCTION_LIST_PTR flp = 0;
	rv = gfl(&flp);

	printf("Ret value of GetListPtr (%d)\n", rv);

	CK_C_Initialize func = flp->C_Initialize;
	// (Re)initialize the token
	rv = (*func)(0);
	printf("Initializing (%d)\n", rv);
	
}
