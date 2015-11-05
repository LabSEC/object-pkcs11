#include "PKCS11CallbackMocker.h"

CK_RV C_Initialize(void *init_args) {
	return pkcs11Mocker.C_Initialize(init_args);
}

CK_RV C_Finalize(void *reserved) {
	pkcs11Mocker.C_Finalize = [&](void* ptr) {
		return CKR_OK;
	};	
	return pkcs11Mocker.C_Finalize(reserved);
}

CK_RV C_GetInfo(CK_INFO *info) {
	return pkcs11Mocker.C_GetInfo(info);
}

CK_RV C_GetSlotList(unsigned char token_present, CK_SLOT_ID *slot_list, unsigned long *count) {
	return pkcs11Mocker.C_GetSlotList(token_present, slot_list, count);
}

CK_RV C_GetSlotInfo(CK_SLOT_ID slot_id, CK_SLOT_INFO *info) {
	return pkcs11Mocker.C_GetSlotInfo(slot_id, info);
}


//TODO Do it for every other function as necessary

CK_FUNCTION_LIST realFunctionList = {
  .version = {0,0},
  .C_Initialize = C_Initialize,
  .C_Finalize = C_Finalize,
  .C_GetInfo = NULL,
  .C_GetFunctionList = C_GetFunctionList,
  .C_GetSlotList = C_GetSlotList,
  .C_GetSlotInfo = C_GetSlotInfo,
  .C_GetTokenInfo = NULL,
  .C_GetMechanismList = NULL,
  .C_GetMechanismInfo = NULL,
  .C_InitToken = NULL,
  .C_InitPIN = NULL,
  .C_SetPIN = NULL,
  .C_OpenSession = NULL,
  .C_CloseSession = NULL,
  .C_CloseAllSessions = NULL,
  .C_GetSessionInfo = NULL,
  .C_GetOperationState = NULL,
  .C_SetOperationState = NULL,
  .C_Login = NULL,
  .C_Logout = NULL,
  .C_CreateObject = NULL,
  .C_CopyObject = NULL,
  .C_DestroyObject = NULL,
  .C_GetObjectSize = NULL,
  .C_GetAttributeValue = NULL,
  .C_SetAttributeValue = NULL,
  .C_FindObjectsInit = NULL,
  .C_FindObjects = NULL,
  .C_FindObjectsFinal = NULL,
  .C_EncryptInit = NULL,
  .C_Encrypt = NULL,
  .C_EncryptUpdate = NULL,
  .C_EncryptFinal = NULL,
  .C_DecryptInit = NULL,
  .C_Decrypt = NULL,
  .C_DecryptUpdate = NULL,
  .C_DecryptFinal = NULL,
  .C_DigestInit = NULL,
  .C_Digest = NULL,
  .C_DigestUpdate = NULL,
  .C_DigestKey = NULL,
  .C_DigestFinal = NULL,
  .C_SignInit = NULL,
  .C_Sign = NULL,
  .C_SignUpdate = NULL,
  .C_SignFinal = NULL,
  .C_SignRecoverInit = NULL,
  .C_SignRecover = NULL,
  .C_VerifyInit = NULL,
  .C_Verify = NULL,
  .C_VerifyUpdate = NULL,
  .C_VerifyFinal = NULL,
  .C_VerifyRecoverInit = NULL,
  .C_VerifyRecover = NULL,
  .C_DigestEncryptUpdate = NULL,
  .C_DecryptDigestUpdate = NULL,
  .C_SignEncryptUpdate = NULL,
  .C_DecryptVerifyUpdate = NULL,
  .C_GenerateKey = NULL,
  .C_GenerateKeyPair = NULL,
  .C_WrapKey = NULL,
  .C_UnwrapKey = NULL,
  .C_DeriveKey = NULL,
  .C_SeedRandom = NULL,
  .C_GenerateRandom = NULL,
  .C_GetFunctionStatus = NULL,
  .C_CancelFunction = NULL,
  .C_WaitForSlotEvent = NULL
};

CK_RV C_GetFunctionList(CK_FUNCTION_LIST **function_list)
{
	*function_list = &realFunctionList;
	return CKR_OK;
}
