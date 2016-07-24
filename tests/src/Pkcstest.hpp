#include "mock/PKCS11CallbackMocker.h"
#include <dlfcn.h>

namespace pkcstest {

	static CK_LAMBDA_FUNCTION_LIST* getMocker() {
		void* mocker = dlopen("/tmp/pkcs11mocked.so", RTLD_LAZY);	
		return (CK_LAMBDA_FUNCTION_LIST*) dlsym(mocker, "pkcs11Mocker");
	}

	static void closeMocker(CK_LAMBDA_FUNCTION_LIST* mocker) {
		if(mocker)
			dlclose(mocker);
			mocker = NULL;
	}

	static void setUpMockerFunctions(CK_LAMBDA_FUNCTION_LIST* pkcs11) { 
		pkcs11->C_Initialize = [&](void* ptr) -> CK_RV {
			return CKR_OK;
		};

		pkcs11->C_Finalize = [&](void* ptr) -> CK_RV {
			return CKR_OK;
		};

		pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {
			return CKR_FUNCTION_FAILED; //ver retorno correto
		};

		pkcs11->C_GetFunctionList = [&](CK_FUNCTION_LIST **) -> CK_RV {
			return CKR_FUNCTION_FAILED;
		};

		pkcs11->C_GetSlotList = [&](unsigned char, CK_SLOT_ID *, unsigned long *) -> CK_RV {
			return CKR_FUNCTION_FAILED;
		};

		pkcs11->C_GetSlotInfo = [&](CK_SLOT_ID, CK_SLOT_INFO*) -> CK_RV {
			return CKR_FUNCTION_FAILED;
		};
	}	

}
