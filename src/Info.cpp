#include "Info.h"
namespace raiki {
std::string Info::version() {
	std::string major = std::to_string(majorVersion());
	std::string minor = std::to_string(minorVersion());
	return major + "." + minor;
}

int Info::majorVersion() {
	return (int)_info.cryptokiVersion.major;
}

int Info::minorVersion() {
	return (int)_info.cryptokiVersion.minor;
}

std::string Info::manufacturerId() {
	return std::string(_info.manufacturerID, _info.manufacturerID + 32);

}

Info::InfoFlags Info::flags() {
	int fl = (int)_info.flags;
	if(fl < 1) {
		return InfoFlags::EMPTY;
	} else if(fl > 7) {
		return InfoFlags::UNKNOWN;
	}
	return static_cast<InfoFlags>(fl);
}

std::string Info::libraryDescription() {
	return std::string(_info.libraryDescription, _info.libraryDescription + 32);
}

std::string Info::libraryVersion() {
	std::string major = std::to_string(libraryMajorVersion());
	std::string minor = std::to_string(libraryMinorVersion());
	return major + "." + minor;
}

int Info::libraryMajorVersion() {
	return (int)_info.libraryVersion.major;
}

int Info::libraryMinorVersion() {
	return (int)_info.libraryVersion.minor;
}

CK_INFO Info::getInfo() {
	return _info;
}

}/*END NAMESPACE*/
