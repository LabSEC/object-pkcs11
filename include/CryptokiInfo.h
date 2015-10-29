#ifndef CRYPTOKIINFO_H
#define CRYPTOKIINFO_H

#include <string>

#include "pkcs11.h"

/*!
 * @brief <b>PKCS#11 Info</b><br>
 *
 * This class is a CK_INFO wrapper, it holds
 * the original struct protected and provides
 * public functions to return its values.
 *
 * @see pkcs11.h
 * @see CK_INFO
 *
 * @author Lucas Pandolfo Perin
 */
class CryptokiInfo
{
public:

	virtual ~CryptokiInfo(){};

	enum CryptokiInfoFlags
	{
		TOKEN_IS_PRESENT = 1,
		REMOVABLE_DEVICE = 2,
		HARDWARE_SLOT = 4,
		TKN_PST_N_RMV_DVC = TOKEN_IS_PRESENT | REMOVABLE_DEVICE,
		TKN_PST_N_HW_SLOT = TOKEN_IS_PRESENT | HARDWARE_SLOT,
		RMV_DVC_N_HW_SLOT = REMOVABLE_DEVICE | HARDWARE_SLOT,
		TKN_PST_N_RMV_DVC_N_HW_SLOT = TKN_PST_N_RMV_DVC | HARDWARE_SLOT
	};

	std::string cryptokiVersion();
	int cryptokiMajorVersion();
	int cryptokiMinorVersion();
	std::string manufacturerId();
	CryptokiInfo::CryptokiInfoFlags flags();
	std::string libraryDescription();
	std::string libraryVersion();
	int libraryMajorVersion();
	int libraryMinorVersion();
	CK_INFO* getInfo();

protected:
	CK_INFO info;
};

#endif /*CRYPTOKIINFO_H*/
