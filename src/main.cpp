#ifndef MAIN_CPP
#define MAIN_CPP

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <regex>
#include <string>
#include <cstring>


#include "P11.h"
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

void printInfo(CryptokiInfo& info)
{
	TRACEm("Manufacturer ID: %s", info.manufacturerId().c_str());
	TRACEm("Cryptoki version: %s", info.cryptokiVersion().c_str());
	TRACEm("Library: %s (version %s)", info.libraryDescription().c_str(), info.libraryVersion().c_str());
}

void testAPI(P11* p11)
{
	std::string soPin = "123456";
	std::string tpin = "123456";
	std::string label = "token1";
	int slot = 1;
	try
	{
		p11->initialize();
		CryptokiInfo info = p11->getInfo();
		printInfo(info);
		CK_FUNCTION_LIST flist = p11->getFunctionList();
		//p11->initToken(slot, soPin, label);
		CryptokiSession session = p11->openSession(slot);
		session.login(soPin);
		p11->initPin(session, tpin);
		p11->finalize();
	}
	catch (P11Exception &e)
	{
		TRACEm_ERROR("%s %lu (%s) at <%s>","Exit with error code: ", 
			e.getErrorCode(), e.what(), e.where());
	}
}

int main(int argc, const char* argv[])
{
	P11* p11;
	if (argv[1] != 0)
	{
		std::string path = argv[1];
		p11 = new P11(path);
	}
	else
	{
		std::string defaultModule = "/usr/lib64/libsofthsm2.so";
		p11 = new P11(defaultModule);
	}
	//init(p11, argc, argv);
	testAPI(p11);
	//CryptokiInfo inf;
	//printInfo(inf);
	
/*
	assert(sym != 0);
	CK_C_GetFunctionList getFuncList = (CK_C_GetFunctionList) dlsym(sym, "C_GetFunctionList");


	CK_FUNCTION_LIST_PTR lp = 0;
	rv = getFuncList(&lp);
	CK_FUNCTION_LIST p11 = *lp;
	assert(rv == CKR_OK);
	TRACE("GetFunctionList::Ok!");



	CK_UTF8CHAR pin[] = SLOT_0_USER1_PIN;
	CK_ULONG pinLength = sizeof(pin) - 1;
	CK_UTF8CHAR sopin[] = SLOT_0_SO1_PIN;
	CK_ULONG sopinLength = sizeof(sopin) - 1;
	CK_SESSION_HANDLE hSession;
	CK_UTF8CHAR label[32];
	memset(label, ' ', 32);
	memcpy(label, "token1", strlen("token1"));

	rv = p11->C_Initialize(0);
	assert(rv == CKR_OK);
	TRACE("Initialize::Ok!");

	rv = p11->C_InitToken(SLOT_INIT_TOKEN, sopin,sopinLength, label);
	assert(rv == CKR_OK);
	TRACE("InitToken::Ok!");

	rv = p11->C_OpenSession(SLOT_INIT_TOKEN, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, NULL_PTR, &hSession);
	assert(rv == CKR_OK);
	TRACE("OpenSession::OK");

	rv = p11->C_Login(hSession,CKU_SO, sopin, sopinLength);
	assert(rv == CKR_OK);
	TRACE("Login::OK");

	rv = p11->C_InitPIN(hSession, pin, pinLength);
	assert(rv == CKR_OK);
	TRACE("InitPin::OK");

	p11->C_Finalize(0);
	dlclose(sym);
	TRACE("Quit..");
*/
}

#endif /*MAIN_CPP*/
