#ifndef INFO_H
#define INFO_H

#include <string>

#include "pkcs11.h"

namespace objck {
/*!
 * @brief <b>PKCS#11 Info</b><br>
 *
 * This class is a CK_INFO wrapper, it holds
 * the original struct protected and provides
 * public functions to return its values.
 *
 * @see Cryptoki
 * @see CK_INFO
 *
 * @author Lucas Pandolfo Perin
 */
class Info {
	friend class Cryptoki;
protected:
	CK_INFO _info;
public:
	Info(){};
	virtual ~Info(){};
	
	enum InfoFlags {
		EMPTY = 0,
		TOKEN_IS_PRESENT = 1,
		REMOVABLE_DEVICE = 2,
		HARDWARE_SLOT = 4,
		TKN_PST_N_RMV_DVC = TOKEN_IS_PRESENT | REMOVABLE_DEVICE,
		TKN_PST_N_HW_SLOT = TOKEN_IS_PRESENT | HARDWARE_SLOT,
		RMV_DVC_N_HW_SLOT = REMOVABLE_DEVICE | HARDWARE_SLOT,
		TKN_PST_N_RMV_DVC_N_HW_SLOT = TKN_PST_N_RMV_DVC | HARDWARE_SLOT,
		UNKNOWN = 32
	};

	std::string version();
	int majorVersion();
	int minorVersion();
	std::string manufacturerId();
	Info::InfoFlags flags();
	std::string libraryDescription();
	std::string libraryVersion();
	int libraryMajorVersion();
	int libraryMinorVersion();
	CK_INFO getInfo();
};
}/*END NAMESPACE*/
#endif /*INFO_H*/
