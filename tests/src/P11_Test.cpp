#include "gtest/gtest.h"
#include "mock/PKCS11CallbackMocker.h"
#include <P11.h>
#include <P11Exception.h>

TEST(P11_Test, Finalize_should_be_called_on_destructor)
{
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("/tmp/pkcs11mocked.so");
	bool called = false;
	pkcs11->C_Finalize = [&](void* ptr) -> CK_RV {
		called = true;
		return CKR_OK;
	};	

	{P11 p11module("/tmp/pkcs11mocked.so");}
	EXPECT_TRUE(called);
}

TEST(P11_Test, Initialize_OK)
{
	P11 p11module("/tmp/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("/tmp/pkcs11mocked.so");
	
	bool called = false;
	pkcs11->C_Initialize = [&](void* ptr) -> CK_RV {
		called = true;
		return CKR_OK;
	};	

	EXPECT_NO_THROW(p11module.initialize());
	EXPECT_TRUE(called);
}

TEST(P11_Test, Initialize_Failed_causes_exception)
{
	P11 p11module("/tmp/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("/tmp/pkcs11mocked.so");
	
	pkcs11->C_Initialize = [&](void* ptr) {
		return CKR_GENERAL_ERROR;
	};	

	try {
		p11module.initialize();
		EXPECT_TRUE(false);
	} catch (P11Exception& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
}

TEST(P11_Class, getInfo)
{

	P11 p11module("/tmp/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("/tmp/pkcs11mocked.so");

	pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {
		//TODO aqui voc'e recebe o endereco de info. Atribua valores a struct e teste depois da chamada.
		info->cryptokiVersion.major = 6;
		info->cryptokiVersion.minor = 7;
		info->flags = 0;
		info->libraryVersion.major = 12;
		info->libraryVersion.minor = 13;

		return CKR_OK;
	};

	CryptokiInfo cryptokiInfo;
	cryptokiInfo = p11module.getInfo();

	ASSERT_EQ(cryptokiInfo.cryptokiMajorVersion(),6);
	ASSERT_EQ(cryptokiInfo.cryptokiMinorVersion(),7);
	ASSERT_EQ(cryptokiInfo.flags(), CryptokiInfo::EMPTY);
	ASSERT_EQ(cryptokiInfo.libraryMajorVersion(),12);
	ASSERT_EQ(cryptokiInfo.libraryMinorVersion(),13);
}

TEST(P11_Class, getInfo_error)
{
	P11 p11module("/tmp/pkcs11mocked.so");
	
	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("/tmp/pkcs11mocked.so");

	pkcs11->C_GetInfo = [&](CK_INFO *info) -> CK_RV {

		return CKR_GENERAL_ERROR;
	};

	try {
		p11module.getInfo();
		EXPECT_TRUE(false);
	} catch (P11Exception& e) {
		EXPECT_EQ(e.getErrorCode(), CKR_GENERAL_ERROR);
	}
}

TEST(P11_Class, getFunction)
{
	P11 p11module("/tmp/pkcs11mocked.so");

	CK_LAMBDA_FUNCTION_LIST* pkcs11 = getMockerReference("/tmp/pkcs11mocked.so");

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
