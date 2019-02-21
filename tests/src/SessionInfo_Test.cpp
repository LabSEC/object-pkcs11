#include "gtest/gtest.h"
#include <SessionInfo.h>
#include <CryptokiException.h>

using namespace raiki;

TEST(SessionInfo_test, constructor) {
	CK_SESSION_INFO info = {
		37,
		CKS_RW_PUBLIC_SESSION,
		CKF_SERIAL_SESSION,
		2
	};
			
	SessionInfo sInfo(info);

	EXPECT_EQ(sInfo.slotId(), 37UL);
	EXPECT_EQ(sInfo.state(), CKS_RW_PUBLIC_SESSION);
	EXPECT_EQ(sInfo.flags(), SessionInfo::SessionFlags::SERIAL_SESSION);
	EXPECT_EQ(sInfo.deviceError(), 2UL);

	CK_SESSION_INFO recoveredInfo = sInfo.getSessionInfo();
	EXPECT_EQ(recoveredInfo.slotID, info.slotID);	
	EXPECT_EQ(recoveredInfo.state, info.state);	
	EXPECT_EQ(recoveredInfo.flags, info.flags);	
	EXPECT_EQ(recoveredInfo.ulDeviceError, info.ulDeviceError);	
}

TEST(SessionInfo_test, empty_and_unknown_flags) {
	CK_SESSION_INFO info = { 0, 0, 0, 0 };
	SessionInfo sInfo(info);

	EXPECT_EQ(sInfo.flags(), SessionInfo::SessionFlags::EMPTY);

	info.flags = 8;
	sInfo = SessionInfo(info);
	EXPECT_EQ(sInfo.flags(), SessionInfo::SessionFlags::UNKNOWN);
}
