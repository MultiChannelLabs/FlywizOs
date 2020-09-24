# Hotspot 설정 액티비티 시작
```c++
EASYUICONTEXT->openActivity("SoftApSettingActivity");
```
# Hotspot 작동 함수 설명
SoftApManager 객체 가져오기
```c++
#include "net/NetManager.h"
SoftApManager *pSAM = NETMANAGER->getSoftApManager();

// You can define a macro to facilitate the following functino calls
#define SOFTAPMANAGER     NETMANAGER->getSoftApManager()
```
Hotspot 켜기
```c++
SOFTAPMANAGER->setEnable(true);
```
Hotspot이 on인지 확인
```c++
SOFTAPMANAGER->isEnable();
```
현재 hotspot 상태 가져오기
```c++
SOFTAPMANAGER->getSoftApState();

// There are the following states
E_SOFTAP_DISABLED	// Disabled
E_SOFTAP_ENABLING	// During tunning on
E_SOFTAP_ENABLED	// Turn on successfully
E_SOFTAP_DISABLING // During tunning off
E_SOFTAP_ENABLE_ERROR	// Turn on failed
```
Hotspot 이름 및 패스워드 설정
```c++
SOFTAPMANAGER->setSsidAndPwd("zkswe", "abcd1234");
```
Hotspot 이름 및 패스워드 가져오기
```c++
SOFTAPMANAGER->getSsid();
SOFTAPMANAGER->getPwd();
```
Hotspot 상태 모니터링함수 등록 및 해제
```c++
void addSoftApStateListener(ISoftApStateListener *pListener);
void removeSoftApStateListener(ISoftApStateListener *pListener);
```