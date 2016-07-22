#include "gtest/gtest.h"
#include "Pkcstest.hpp"
#include <Cryptoki.h>
#include <CryptokiException.h>

using namespace objck;
class Cryptoki_Test : public ::testing::Test {

protected :

	static CK_LAMBDA_FUNCTION_LIST* pkcs11;

	/*Set up after each test fixture*/
	static void SetUpTestCase() {
		pkcs11 = pkcstest::getMocker();
		pkcstest::setUpMockerFunctions(pkcs11);
	}

	/*Tear down after each test fixture*/
	static void TearDownTestCase() {
		pkcstest::closeMocker(pkcs11);
	}

	/*Set up before running test fixtures*/
	void SetUp() {
	}

	/*Tear down loaded mocker*/
	void TearDown() {}
};

CK_LAMBDA_FUNCTION_LIST* Cryptoki_Test::pkcs11 = NULL; 

TEST_F(Cryptoki_Test, LoadModule_causes_exception) {
	try {
		Cryptoki p11module("wrong/path.so");
	} catch (CryptokiException& e) {
		//TODO(perin): this exception code may change in Cryptoki class source
		EXPECT_EQ(e.getErrorCode(), 666);
	}

}

TEST_F(Cryptoki_Test, LoadFunctions_causes_exception) {
	pkcs11Mocker.C_GetFunctionList = [&](CK_FUNCTION_LIST**) -> CK_RV {
		return CKR_GENERAL_ERROR;
	};
	try {
		Cryptoki p11module("/tmp/pkcs11mocked.so");
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}

}

TEST_F(Cryptoki_Test, Finalize_should_be_called_on_destructor) {
	bool called = false;
	pkcs11->C_Finalize = [&](void* ptr) -> CK_RV {
		called = true;
		return CKR_OK;
	};	

	{Cryptoki p11module("/tmp/pkcs11mocked.so");}
	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, Initialize_OK)
{
	Cryptoki p11module("/tmp/pkcs11mocked.so");
	
	bool called = false;
	pkcs11->C_Initialize = [&](void* ptr) -> CK_RV {
		called = true;
		return CKR_OK;
	};	

	EXPECT_NO_THROW(p11module.initialize());
	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, Initialize_Failed_causes_exception)
{
	Cryptoki p11module("/tmp/pkcs11mocked.so");
		
	pkcs11->C_Initialize = [&](void* ptr) {
		return CKR_GENERAL_ERROR;
	};	

	try {
		p11module.initialize();
		EXPECT_TRUE(false);
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
}

TEST_F(Cryptoki_Test, getInfo)
{
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {
		info->cryptokiVersion.major = 6;
		info->cryptokiVersion.minor = 7;
		info->flags = 0;
		info->libraryVersion.major = 12;
		info->libraryVersion.minor = 13;
		memcpy(info->manufacturerID, "Perinovsky                      ", 32);
		memcpy(info->libraryDescription, "Claud Computing                 ", 32);
		return CKR_OK;
	};

	Info info;
	info = p11module.getInfo();

	ASSERT_EQ(info.majorVersion(),6);
	ASSERT_EQ(info.minorVersion(),7);
	ASSERT_EQ(info.version(),"6.7");
	ASSERT_EQ(info.manufacturerId(), "Perinovsky                      ");
	ASSERT_EQ(info.libraryDescription(), "Claud Computing                 ");
	ASSERT_EQ(info.flags(), Info::EMPTY); 
	ASSERT_EQ(info.libraryMajorVersion(),12);
	ASSERT_EQ(info.libraryMinorVersion(),13);
	ASSERT_EQ(info.libraryVersion(),"12.13");

	CK_INFO recoveredStruct = info.getInfo();
	ASSERT_EQ(recoveredStruct.cryptokiVersion.major, 6);
	ASSERT_EQ(recoveredStruct.cryptokiVersion.minor, 7);
	ASSERT_EQ(recoveredStruct.flags, 0);
	ASSERT_EQ(recoveredStruct.libraryVersion.major, 12);
	ASSERT_EQ(recoveredStruct.libraryVersion.minor, 13);
	ASSERT_FALSE(memcmp(recoveredStruct.manufacturerID, "Perinovsky                      ", 32));
	ASSERT_FALSE(memcmp(recoveredStruct.libraryDescription, "Claud Computing                 ", 32));
}

TEST_F(Cryptoki_Test, info_can_handle_unknown_flags)
{
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {
		info->flags = 8;
		return CKR_OK;
	};

	Info info;
	CK_INFO recoveredStruct;
	
    info = p11module.getInfo();
	ASSERT_EQ(info.flags(), Info::UNKNOWN); 
	recoveredStruct = info.getInfo();
	ASSERT_EQ(recoveredStruct.flags, 8);

	pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {
		info->flags = 4;
		return CKR_OK;
	};

	info = p11module.getInfo();
	ASSERT_EQ(info.flags(), Info::HARDWARE_SLOT); 
	recoveredStruct = info.getInfo();
	ASSERT_EQ(recoveredStruct.flags, 4);
}

TEST_F(Cryptoki_Test, getInfo_error)
{
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {

		return CKR_GENERAL_ERROR;
	};

	try {
		p11module.getInfo();
		EXPECT_TRUE(false);
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
}

TEST_F(Cryptoki_Test, getFunctionList)
{
	Cryptoki p11module("/tmp/pkcs11mocked.so");

  	bool called = false;
	pkcs11->C_Initialize = [&](void* ptr) -> CK_RV {
		EXPECT_EQ(ptr, (void*)0x123456);
		called = true;
		return CKR_OK;
	};

	FunctionList test = p11module.getFunctionList();
		
	EXPECT_NO_THROW({
		CK_RV rv = (*test.C_Initialize)((void*)0x123456);
		EXPECT_EQ(rv, CKR_OK);
	});
	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, GetFunctionList_causes_exception) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	pkcs11Mocker.C_GetFunctionList = [&](CK_FUNCTION_LIST**) -> CK_RV {
		return CKR_GENERAL_ERROR;
	};

	try {
		FunctionList test = p11module.getFunctionList();
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}

}

TEST_F(Cryptoki_Test, initToken) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	bool called = false;
	std::string pin = "123456";
	std::string label = "test";

	pkcs11->C_InitToken = [&](CK_SLOT_ID slot_id, unsigned char *pin, 
		unsigned long pin_len, unsigned char *label) -> CK_RV {
		called = true;
		//TODO(perin): compare strings?
		return CKR_OK;
	};

	EXPECT_NO_THROW(p11module.initToken(0, pin, label));
	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, initToken_Failed_causes_exception) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	bool called = false;

	pkcs11->C_InitToken = [&](CK_SLOT_ID slot_id, unsigned char *pin, 
		unsigned long pin_len, unsigned char *label) -> CK_RV {
		called = true;
		return CKR_GENERAL_ERROR;
	};

	std::string pin = "123456";
	std::string label = "test";
	try {
		p11module.initToken(0, pin, label);
		EXPECT_TRUE(false);
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, object_pkcs11_can_login) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	bool called = false;

    pkcs11->C_OpenSession = [&](CK_SLOT_ID slot_id, CK_FLAGS flags, void *application, CK_NOTIFY notify, CK_SESSION_HANDLE *session) -> CK_RV {
        *session = 0x123456;
		return CKR_OK;
	};
  
    pkcs11->C_CloseSession = [&](CK_SESSION_HANDLE session) -> CK_RV {
		return CKR_OK;
	};
  
    pkcs11->C_Login = [&](CK_SESSION_HANDLE session, CK_USER_TYPE user_type, unsigned char *pin, unsigned long pin_len) -> CK_RV {
        called = true;
        EXPECT_EQ(session, 0x123456);

        return CKR_OK;
    };

	std::string pin = "123456";
	try {
		Session session = p11module.openSession(0, SessionInfo::SessionFlags::RW_SESSION, 0, 0);
        session.userLogin(pin);
	} catch (CryptokiException& e) {
		ASSERT_TRUE(false);
	}
	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, error_on_login_causes_exception) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	bool called = false;

    pkcs11->C_OpenSession = [&](CK_SLOT_ID slot_id, CK_FLAGS flags, void *application, CK_NOTIFY notify, CK_SESSION_HANDLE *session) -> CK_RV {
        *session = 0x123456;
		return CKR_OK;
	};
  
    pkcs11->C_CloseSession = [&](CK_SESSION_HANDLE session) -> CK_RV {
		return CKR_OK;
	};
  
    pkcs11->C_Login = [&](CK_SESSION_HANDLE session, CK_USER_TYPE user_type, unsigned char *pin, unsigned long pin_len) -> CK_RV {
        called = true;
        return CKR_GENERAL_ERROR;
    };

	std::string pin = "123456";
	
    try {
		Session session = p11module.openSession(0, SessionInfo::SessionFlags::RW_SESSION, 0, 0);
        session.userLogin(pin);
		EXPECT_TRUE(false);
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}

	EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, open_session_works_with_error) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	bool called = false;

    pkcs11->C_OpenSession = [&](CK_SLOT_ID slot_id, CK_FLAGS flags, void *application, CK_NOTIFY notify, CK_SESSION_HANDLE *session) -> CK_RV {
	    called = true;
		return CKR_GENERAL_ERROR;
	};
  
	try {
		Session session = p11module.openSession(0, SessionInfo::SessionFlags::RW_SESSION, 0, 0);
		EXPECT_TRUE(false);
	} catch (CryptokiException& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
	
    EXPECT_TRUE(called);
}

TEST_F(Cryptoki_Test, close_session_works_with_error) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

	bool opencalled = false;
    bool closecalled = false;

    pkcs11->C_OpenSession = [&](CK_SLOT_ID slot_id, CK_FLAGS flags, void *application, CK_NOTIFY notify, CK_SESSION_HANDLE *session) -> CK_RV {
        opencalled = true;
        *session = 0x123456;
		return CKR_OK;
	};
    
    pkcs11->C_CloseSession = [&](CK_SESSION_HANDLE session) -> CK_RV {
		closecalled = true;
        return CKR_GENERAL_ERROR;
	};
  
 
    bool gotexception = false; 
	try {
		Session session = p11module.openSession(0, SessionInfo::SessionFlags::RW_SESSION, 0, 0);
        EXPECT_TRUE(opencalled);
        EXPECT_FALSE(closecalled);
        session.closeSession();
    } catch (CryptokiException& e) {
        gotexception = true;
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
	
    EXPECT_TRUE(closecalled);
    EXPECT_TRUE(gotexception);
}

TEST_F(Cryptoki_Test, close_all_sessions_works) {
	Cryptoki p11module("/tmp/pkcs11mocked.so");

    bool called = false;

    pkcs11->C_OpenSession = [&](CK_SLOT_ID slot_id, CK_FLAGS flags, void *application, CK_NOTIFY notify, CK_SESSION_HANDLE *session) -> CK_RV {
		return CKR_OK;
	};
    
    pkcs11->C_CloseAllSessions = [&](int slot) -> CK_RV {
        called = true;
        return CKR_OK;
	};
	

    try {
		Session session = p11module.openSession(0, SessionInfo::SessionFlags::RW_SESSION, 0, 0);
        p11module.closeAllSessions(5);
        ASSERT_TRUE(called);
    } catch (CryptokiException& e) {
		ASSERT_TRUE(false);
	}
  
    pkcs11->C_CloseAllSessions = [&](int slot) -> CK_RV {
        called = true;
        return CKR_GENERAL_ERROR;
	};
 
    bool gotexception = false; 
    called = false;
	try {
		Session session = p11module.openSession(0, SessionInfo::SessionFlags::RW_SESSION, 0, 0);
        p11module.closeAllSessions(5);
    } catch (CryptokiException& e) {
        gotexception = true;
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
	
    EXPECT_TRUE(called);
    EXPECT_TRUE(gotexception);
}
