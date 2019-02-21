#include "Cryptoki.h"

namespace raiki {

Cryptoki::Cryptoki() noexcept : _module(0), _functionList(0) {
	//Nothing to do? We should not load any module here for safety.
}

Cryptoki::Cryptoki(std::string path) : _module(0), _functionList(0) {
	loadModule(path);
}

Cryptoki::~Cryptoki() {
	if(_module)
	{
		finalize();
		dlclose(_module);
	}
}

void Cryptoki::loadModule(const std::string& path) {
	/* Change to RTLD_LAZY if loading is slow*/
	_module = dlopen(path.c_str(), RTLD_NOW);
	if (!_module) {
		//TODO(perin): Should use different exception code?
		throw CryptokiException(dlerror(), 666);
	}
	loadFunctions();
}

void Cryptoki::loadFunctions() {
	dlerror();
	CK_C_GetFunctionList getFuncList = reinterpret_cast<CK_C_GetFunctionList>(dlsym(_module, "C_GetFunctionList"));
	char* err;
	if( (err = dlerror()) != NULL) {
		//TODO(perin): Should use different exception code?
		throw CryptokiException(err, 666);
	}

	_functionList = NULL;
	CK_RV rv  = getFuncList(&_functionList);
	if(rv) {	
		throw CryptokiException("Expected CKR_OK from C_GetFunctionList", rv);
	}

	if(!_functionList) {
		//TODO(perin): Should use different exception code?
		throw CryptokiException("Could not load function list.", 666);
	}
}

void Cryptoki::initialize() {
	PRECONDITION(_functionList->C_Initialize);
	CK_RV rv  = (*_functionList->C_Initialize)(0);
	if(rv) 	{
		throw CryptokiException("Failed to initialize module.", rv);
	}
}

void Cryptoki::finalize() {
	PRECONDITION(_functionList->C_Finalize);
	(*_functionList->C_Finalize)(0);
}

Info Cryptoki::getInfo() {
	PRECONDITION(_functionList->C_GetInfo);
	Info cryptokiInfo;
	CK_RV rv  = (*_functionList->C_GetInfo)(&cryptokiInfo._info);
	if(rv) 	{
		throw CryptokiException(rv);
	}
	return cryptokiInfo;
}

FunctionList Cryptoki::getFunctionList()
{
	PRECONDITION(_functionList->C_GetFunctionList);
	CK_FUNCTION_LIST_PTR fListPtr;
	
	CK_RV rv  = (*_functionList->C_GetFunctionList)(&fListPtr);
	if(rv)
	{
		throw CryptokiException(rv);
	}
	return *fListPtr;
}

//TODO(perin): copy strings without casting. CK_UTF8CHAR is unsigned char.
void Cryptoki::initToken(unsigned int slot, std::string& soPin, std::string& label)
{
	PRECONDITION(_functionList->C_InitToken);
	CK_ULONG soPinLen = soPin.length();
	CK_UTF8CHAR* utf8soPin = new CK_UTF8CHAR[soPin.length()];
	strncpy((char*)utf8soPin, soPin.c_str(), soPin.length());

	CK_UTF8CHAR* utf8label = new CK_UTF8CHAR[label.length()];
	strncpy((char*)utf8label, label.c_str(), label.length());

	CK_RV rv  = (*_functionList->C_InitToken)(slot, utf8soPin, soPinLen, utf8label);
	if(rv)
	{
		throw CryptokiException(rv);
	}
}

Session Cryptoki::openSession(unsigned int slot, SessionInfo::SessionFlags flags, CryptokiNotify* notify, void* appPtr)
{
	PRECONDITION(_functionList->C_OpenSession);
	Session sn;
	//TODO(Perin): Implement notify callbacks
    CK_RV rv  = (*_functionList->C_OpenSession)(slot, flags, 0, 0, &sn._session);
    if(rv)
        {
            throw CryptokiException(rv);
        }
	sn._functionList = _functionList;
	sn.enable();
	return sn;
}

void Cryptoki::closeAllSessions(unsigned int slot)
{
	PRECONDITION(_functionList->C_CloseAllSessions);
	CK_RV rv  = (_functionList->C_CloseAllSessions)(slot);
    if(rv)
        {
            throw CryptokiException(rv);
        }
}

}/*END NAMESPACE*/
