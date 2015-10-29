#include "CryptokiInfo.h"

std::string CryptokiInfo::cryptokiVersion()
{
	std::string major = std::to_string(cryptokiMajorVersion());
	std::string minor = std::to_string(cryptokiMinorVersion());
	return major + "." + minor;
}

int CryptokiInfo::cryptokiMajorVersion()
{
	return (int)this->info.cryptokiVersion.major;
}

int CryptokiInfo::cryptokiMinorVersion()
{
	return (int)this->info.cryptokiVersion.minor;
}

std::string CryptokiInfo::manufacturerId()
{
	return std::string(reinterpret_cast<const char*>(this->info.manufacturerID));
}

CryptokiInfo::CryptokiInfoFlags CryptokiInfo::flags()
{
	int fl = (int)this->info.flags;
	if(fl < 1)
	{
		return CryptokiInfoFlags::EMPTY;
	}
	else if(fl > 7)
	{
		return CryptokiInfoFlags::UNKNOWN;
	}
	return static_cast<CryptokiInfoFlags>(fl);
}

std::string CryptokiInfo::libraryDescription()
{
	return std::string(reinterpret_cast<const char*>(this->info.libraryDescription));
}

std::string CryptokiInfo::libraryVersion()
{
	std::string major = std::to_string(libraryMajorVersion());
	std::string minor = std::to_string(libraryMinorVersion());
	return major + "." + minor;

}

int CryptokiInfo::libraryMajorVersion()
{
	return (int)this->info.libraryVersion.major;
}

int CryptokiInfo::libraryMinorVersion()
{
	return (int)this->info.libraryVersion.minor;
}

CK_INFO CryptokiInfo::getInfo()
{
	return this->info;
}
