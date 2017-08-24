C++ Object Oriented Wrapper for PKCS#11
=======
[![Build Status](https://travis-ci.org/LabSEC/object-pkcs11.svg?branch=master)](https://travis-ci.org/LabSEC/object-pkcs11)
[![Coverage Status](https://coveralls.io/repos/github/LabSEC/object-pkcs11/badge.svg?branch=dev)](https://coveralls.io/github/LabSEC/object-pkcs11?branch=dev)

# Introduction

Recently I had to prototype some PKCS#11 code to test if the API supported
symmetric key wrapping and double wrapping using RSA and ECDSA public keys.
Coding with C, reading huge pdf docs and header files is just annoying. This
is why I decided to start a PKCS#11 Object Oriented and well documented library.
I hope it helps me and my team mates with our current projects. Moreover, if
it suits you, please feel free to use, share and contribute :)

My goal is to implement this library to work with simple use cases and less code.
If you wish to implement more complex applications, I recommend taking a look at
Libp11 from OpenSC project.

# Contribution

We are designing our objects to be used with RAII pattern. Functions should always
return copies and pointers are not welcome for the end user (should be kept behind
curtain). Sessions are closed the object is destructed. Always consider the 
context of the declaration to manage "close" and "finalize" functions.


# Tests

We wrote a PKCS11 mocker using std::functions. In the test files we can write the
PKCS11 function implementations on the fly. This allows us to test multiple scenarios
without writing multiple mockers.

run the tests with:

	$ make test

# Status
Under development as of Oct 2015.

The following table describes which PKCS11 functions are supported. Although they are not completely supported (maybe), the tests should be a good measure of what we support or not. An OK mark should mean that at least the function is used somewhere in the code.

| Function Name         | Status        |
| --------------------- | ------------- |
| C_Initialize          | OK            |
| C_Finalize            | OK            |
| C_GetInfo             | OK            |
| C_GetFunctionList     | OK            |
| C_GetSlotList         |               |
| C_GetSlotInfo         |               |
| C_GetTokenInfo        |               |
| C_GetMechanismList    |               |
| C_GetMechanismInfo    |               |
| C_InitToken           | OK            |
| C_InitPIN             |               |
| C_SetPIN              |               |
| C_OpenSession         | OK            |
| C_CloseSession        | OK            |
| C_CloseAllSessions    | OK            |
| C_GetSessionInfo      | OK            |
| C_GetOperationState   |               |
| C_SetOperationState   |               |
| C_Login               |               |
| C_Logout              |               |
| C_CreateObject        |               |
| C_CopyObject          |               |
| C_DestroyObject       |               |
| C_GetObjectSize       |               |
| C_GetAttributeValue   |               |
| C_SetAttributeValue   |               |
| C_FindObjectsInit     |               |
| C_FindObjects         |               |
| C_FindObjectsFinal    |               |
| C_EncryptInit         |               |
| C_Encrypt             |               |
| C_EncryptUpdate       |               |
| C_EncryptFinal        |               |
| C_DecryptInit         |               |
| C_Decrypt             |               |
| C_DecryptUpdate       |               |
| C_DecryptFinal        |               |
| C_DigestInit          |               |
| C_Digest              |               |
| C_DigestUpdate        |               |
| C_DigestKey           |               |
| C_DigestFinal         |               |
| C_SignInit            |               |
| C_Sign                |               |
| C_SignUpdate          |               |
| C_SignFinal           |               |
| C_SignRecoverInit     |               |
| C_SignRecover         |               |
| C_VerifyInit          |               |
| C_Verify              |               |
| C_VerifyUpdate        |               |
| C_VerifyFinal         |               |
| C_VerifyRecoverInit   |               |
| C_VerifyRecover       |               |
| C_DigestEncryptUpdate |               |
| C_DecryptDigestUpdate |               |
| C_SignEncryptUpdate   |               |
| C_DecryptVerifyUpdate |               |
| C_GenerateKey         |               |
| C_GenerateKeyPair     |               |
| C_WrapKey             |               |
| C_UnwrapKey           |               |
| C_DeriveKey           |               |
| C_SeedRandom          |               |
| C_GenerateRandom      |               |
| C_GetFunctionStatus   |               |
| C_CancelFunction      |               |
| C_WaitForSlotEvent    |               |

