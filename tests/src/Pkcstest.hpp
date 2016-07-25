#include "mock/PKCS11CallbackMocker.h"
#include <dlfcn.h>
#include <iostream>

namespace pkcstest {

	static Pkcs11Mocker& getMocker() {
		void* mockerHandle = dlopen("/tmp/pkcs11mocked.so", RTLD_NOW | RTLD_GLOBAL);
		if(!mockerHandle) {
			std::cerr << "Could not load mocker binary: " << dlerror() << std::endl;
			exit(1);
		}
		
		dlerror();
		char* err;
		Pkcs11Mocker& (*getMockerInstance)() = (Pkcs11Mocker&(*)()) dlsym(mockerHandle, "getMockerInstance");
		
		if( (err = dlerror()) != NULL) {
			std::cerr << "Could not load symbol \"getMockerInstance\": " << dlerror() << std::endl;
			exit(1);
		}

		return getMockerInstance();
	}

	static void resetFunctionList() {
		getMocker().C_GetFunctionList = nullptr;
	}

	static void setUpMockerFunctions() { 
		getMocker().C_Initialize = [&](void* ptr) -> CK_RV {
			return CKR_OK;
		};

		getMocker().C_Finalize = [&](void* ptr) -> CK_RV {
			return CKR_OK;
		};

		getMocker().C_GetInfo = [&](CK_INFO *info) -> CK_RV {
			return CKR_FUNCTION_FAILED; //ver retorno correto
		};

		getMocker().C_GetFunctionList = [&](CK_FUNCTION_LIST **) -> CK_RV {
			return CKR_FUNCTION_FAILED;
		};

		getMocker().C_GetSlotList = [&](unsigned char, CK_SLOT_ID *, unsigned long *) -> CK_RV {
			return CKR_FUNCTION_FAILED;
		};

		getMocker().C_GetSlotInfo = [&](CK_SLOT_ID, CK_SLOT_INFO*) -> CK_RV {
			return CKR_FUNCTION_FAILED;
		};
	}	

}
