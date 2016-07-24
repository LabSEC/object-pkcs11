#include "mock/PKCS11CallbackMocker.h"
#include <dlfcn.h>
#include <iostream>

namespace pkcstest {

	static CK_LAMBDA_FUNCTION_LIST* getMocker() {
		/* Change to RTLD_LAZY if loading is slow*/
		void* handle = dlopen("/tmp/pkcs11mocked.so", RTLD_NOW);
		if(!handle) {
			std::cerr << "Could not load mocker binary: " << dlerror() << std::endl;
			exit(1);
		}
		
		dlerror();
		CK_LAMBDA_FUNCTION_LIST* mocker = (CK_LAMBDA_FUNCTION_LIST*) dlsym(handle, "pkcs11Mocker");
		char* err;
		
		if( (err = dlerror()) != NULL) {
			std::cerr << "Could not load symbol \"pkcs11Mocker\": " << dlerror() << std::endl;
			exit(1);
		}
		return mocker;
	}

	static void closeMocker(CK_LAMBDA_FUNCTION_LIST* mocker) {
		if(mocker){
			dlclose(mocker);
			mocker = NULL;
		}
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
