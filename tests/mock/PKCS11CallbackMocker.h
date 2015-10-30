#include "pkcs11.h"

extern CK_FUNCTION_LIST pkcs11Mocker;

CK_RV C_GetFunctionList(struct ck_function_list **function_list);
