#include "P11.h"

P11::P11(std::string &path) {
//TODO(perin): check if module was loaded correctly.
	functionList = 0;
	loadModule(path);	
	loadFunctions();
}

P11::~P11() {
	if(this->module){
		TRACE("Cleaning up module.");
		dlclose(module);
	}
}

void P11::loadModule(std::string &path) {
	//TODO(perin): check if module is already loaded;
	TRACE("Loading module from PATH");
	this->module = dlopen(path.c_str(), RTLD_LAZY);
}

void P11::loadFunctions() {
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(module, "C_GetFunctionList");
	rv = getFuncList(&functionList);
	assert(rv == 0);
	TRACE("PKCS11 functions load success.");
}

void P11::initialize() {
	rv = (*functionList->C_Initialize)(0);
	assert(rv == 0);
	TRACE("Cryptoki initialization success.");
}

void P11::finalize() {
	(*functionList->C_Finalize)(0);
	TRACE("Cryptoki finalized.");
}

CK_INFO P11::getInfo() {
	CK_INFO info;
	rv = (*functionList->C_GetInfo)(&info);
	assert(rv == 0);
	TRACE("GetInfo success.");
	return info;
}

CK_FUNCTION_LIST P11::getFunctionList() {
	CK_FUNCTION_LIST_PTR fList;
	rv = (*functionList->C_GetFunctionList)(&fList);
	assert(rv == 0);
	TRACE("GetFunctionList success.");
	return *fList;
}

void P11::initToken(unsigned int slot, std::string &soPin, std::string &label) {
	TRACE(NOT_IMPLEMENTED);
}

void P11::initPin() {
	TRACE(NOT_IMPLEMENTED);
}

void P11::openSession() {
	TRACE(NOT_IMPLEMENTED);
}

void P11::login() {
	TRACE(NOT_IMPLEMENTED);
}

