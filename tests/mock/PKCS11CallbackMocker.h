#include "pkcs11.h"
#include <functional>
#include <dlfcn.h>

typedef struct CK_LAMBDA_FUNCTION_LIST_ST
{
  std::function<CK_RV(void *)> C_Initialize;
  std::function<CK_RV(void *)> C_Finalize;
  std::function<CK_RV(CK_INFO *info)> C_GetInfo;
  std::function<CK_RV(CK_FUNCTION_LIST **)> C_GetFunctionList;
  std::function<CK_RV(unsigned char, CK_SLOT_ID *, unsigned long *)> C_GetSlotList;
  std::function<CK_RV(CK_SLOT_ID, CK_SLOT_INFO*)> C_GetSlotInfo;
  std::function<CK_RV(CK_SLOT_ID, CK_TOKEN_INFO *)> C_GetTokenInfo;
  std::function<CK_RV(CK_FLAGS, CK_SLOT_ID *, void *)> C_WaitForSlotEvent;
  std::function<CK_RV(CK_SLOT_ID slot_id, CK_MECHANISM_TYPE *mechanism_list, unsigned long *count)> C_GetMechanismList;
  std::function<CK_RV(CK_SLOT_ID slot_id, CK_MECHANISM_TYPE type, struct ck_mechanism_info *info)> C_GetMechanismInfo;
  std::function<CK_RV(CK_SLOT_ID slot_id, unsigned char *pin, unsigned long pin_len, unsigned char *label)> C_InitToken;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *pin, unsigned long pin_len)> C_InitPIN;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *old_pin, unsigned long old_len, unsigned char *new_pin, unsigned long new_len)> C_SetPIN;
  std::function<CK_RV(CK_SLOT_ID slot_id, CK_FLAGS flags, void *application, CK_NOTIFY notify, CK_SESSION_HANDLE *session)> C_OpenSession;
  std::function<CK_RV(CK_SESSION_HANDLE session)> C_CloseSession;
  std::function<CK_RV(CK_SLOT_ID slot_id)> C_CloseAllSessions;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_session_info *info)> C_GetSessionInfo;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *operation_state, unsigned long *operation_state_len)> C_GetOperationState;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *operation_state, unsigned long operation_state_len, CK_OBJECT_HANDLE encryption_key, CK_OBJECT_HANDLE authentiation_key)> C_SetOperationState;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_USER_TYPE user_type, unsigned char *pin, unsigned long pin_len)> C_Login;
  std::function<CK_RV(CK_SESSION_HANDLE session)> C_Logout;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_attribute *templ, unsigned long count, CK_OBJECT_HANDLE *object)> C_CreateObject;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE object, struct ck_attribute *templ, unsigned long count, CK_OBJECT_HANDLE *new_object)> C_CopyObject;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE object)> C_DestroyObject;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE object, unsigned long *size)> C_GetObjectSize;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE object, struct ck_attribute *templ, unsigned long count)> C_GetAttributeValue;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE object, struct ck_attribute *templ, unsigned long count)> C_SetAttributeValue;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_attribute *templ, unsigned long count)> C_FindObjectsInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE *object, unsigned long max_object_count, unsigned long *object_count)> C_FindObjects;
  std::function<CK_RV(CK_SESSION_HANDLE session)> C_FindObjectsFinal;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE key)> C_EncryptInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *data, unsigned long data_len, unsigned char *encrypted_data, unsigned long *encrypted_data_len)> C_Encrypt;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *part, unsigned long part_len, unsigned char *encrypted_part, unsigned long *encrypted_part_len)> C_EncryptUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *last_encrypted_part, unsigned long *last_encrypted_part_len)> C_EncryptFinal;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE key)> C_DecryptInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *encrypted_data, unsigned long encrypted_data_len, unsigned char *data, unsigned long *data_len)> C_Decrypt;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *encrypted_part, unsigned long encrypted_part_len, unsigned char *part, unsigned long *part_len)> C_DecryptUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *last_part, unsigned long *last_part_len)> C_DecryptFinal;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism)> C_DigestInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *data, unsigned long data_len, unsigned char *digest, unsigned long *digest_len)> C_Digest;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *part, unsigned long part_len)> C_DigestUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE key)> C_DigestKey;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *digest, unsigned long *digest_len)> C_DigestFinal;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE key)> C_SignInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *data, unsigned long data_len, unsigned char *signature, unsigned long *signature_len)> C_Sign;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *part, unsigned long part_len)> C_SignUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *signature, unsigned long *signature_len)> C_SignFinal;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE key)> C_SignRecoverInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *data, unsigned long data_len, unsigned char *signature, unsigned long *signature_len)> C_SignRecover;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE key)> C_VerifyInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *data, unsigned long data_len, unsigned char *signature, unsigned long signature_len)> C_Verify;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *part, unsigned long part_len)> C_VerifyUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *signature, unsigned long signature_len)> C_VerifyFinal;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE key)> C_VerifyRecoverInit;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *signature, unsigned long signature_len, unsigned char *data, unsigned long *data_len)> C_VerifyRecover;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *part, unsigned long part_len, unsigned char *encrypted_part, unsigned long *encrypted_part_len)> C_DigestEncryptUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *encrypted_part, unsigned long encrypted_part_len, unsigned char *part, unsigned long *part_len)> C_DecryptDigestUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *part, unsigned long part_len, unsigned char *encrypted_part, unsigned long *encrypted_part_len)> C_SignEncryptUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *encrypted_part, unsigned long encrypted_part_len, unsigned char *part, unsigned long *part_len)> C_DecryptVerifyUpdate;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, struct ck_attribute *templ, unsigned long count, CK_OBJECT_HANDLE *key)> C_GenerateKey;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, struct ck_attribute *public_key_template, unsigned long public_key_attribute_count, struct ck_attribute *private_key_template, unsigned long private_key_attribute_count, CK_OBJECT_HANDLE *public_key, CK_OBJECT_HANDLE *private_key)> C_GenerateKeyPair;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE wrapping_key, CK_OBJECT_HANDLE key, unsigned char *wrapped_key, unsigned long *wrapped_key_len)> C_WrapKey;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE unwrapping_key, unsigned char *wrapped_key, unsigned long wrapped_key_len, struct ck_attribute *templ, unsigned long attribute_count, CK_OBJECT_HANDLE *key)> C_UnwrapKey;
  std::function<CK_RV(CK_SESSION_HANDLE session, struct ck_mechanism *mechanism, CK_OBJECT_HANDLE base_key, struct ck_attribute *templ, unsigned long attribute_count, CK_OBJECT_HANDLE *key)> C_DeriveKey;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *seed, unsigned long seed_len)> C_SeedRandom;
  std::function<CK_RV(CK_SESSION_HANDLE session, unsigned char *random_data, unsigned long random_len)> C_GenerateRandom;
  std::function<CK_RV(CK_SESSION_HANDLE session)> C_GetFunctionStatus;
  std::function<CK_RV(CK_SESSION_HANDLE session)> C_CancelFunction;
} CK_LAMBDA_FUNCTION_LIST;

CK_LAMBDA_FUNCTION_LIST pkcs11Mocker;

CK_RV C_GetFunctionList(CK_FUNCTION_LIST **function_list);

CK_LAMBDA_FUNCTION_LIST* getMockerReference(const std::string& path) {
	void* lib = dlopen(path.c_str(), RTLD_LAZY);
	return (CK_LAMBDA_FUNCTION_LIST*) dlsym(lib, "pkcs11Mocker");
}

