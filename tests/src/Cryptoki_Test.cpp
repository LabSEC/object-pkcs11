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

TEST_F(Cryptoki_Test, Finalize_should_be_called_on_destructor)
{
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

		return CKR_OK;
	};

	Info cryptokiInfo;
	cryptokiInfo = p11module.getInfo();

	ASSERT_EQ(Info.majorVersion(),6);
	ASSERT_EQ(Info.minorVersion(),7);
	ASSERT_EQ(Info.flags(), Info::EMPTY); 
	ASSERT_EQ(Info.libraryMajorVersion(),12);
	ASSERT_EQ(Info.libraryMinorVersion(),13);
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

TEST_F(Cryptoki_Test, getFunction)
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
