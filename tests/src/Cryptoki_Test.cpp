#include "gtest/gtest.h"
#include "Pkcstest.hpp"
#include <Cryptoki.h>
#include <CryptokiException.h>

using namespace objck;
class Cryptoki_Test : public ::testing::Test {

protected :

	static CK_LAMBDA_FUNCTION_LIST* pkcs11;

	static void SetUpTestCase() {
		pkcs11 = pkcstest::getMocker();
	}

	static void TearDownTestCase() {}

	void SetUp()
	{
		pkcstest::setUpMockerFunctions(pkcs11);
	}
};

CK_LAMBDA_FUNCTION_LIST* Cryptoki_Test::pkcs11 = NULL; 

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
