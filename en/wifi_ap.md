# Open hotspot setting activity
```c++
EASYUICONTEXT->openActivity("SoftApSettingActivity");
```
# Hotspot operation interface description
Get the SoftApManager object
```c++
#include "net/NetManager.h"
SoftApManager *pSAM = NETMANAGER->getSoftApManager();

// You can define a macro to facilitate the following functino calls
#define SOFTAPMANAGER     NETMANAGER->getSoftApManager()
```
Turn on hotspot
```c++
SOFTAPMANAGER->setEnable(true);
```
Whether the hotspot is on
```c++
SOFTAPMANAGER->isEnable();
```
Get current hotspot state
```c++
SOFTAPMANAGER->getSoftApState();

// There are the following states
E_SOFTAP_DISABLED	// Disabled
E_SOFTAP_ENABLING	// During tunning on
E_SOFTAP_ENABLED	// Turn on successfully
E_SOFTAP_DISABLING // During tunning off
E_SOFTAP_ENABLE_ERROR	// Turn on failed
```
Modify hotspot name and password
```c++
SOFTAPMANAGER->setSsidAndPwd("zkswe", "abcd1234");
```
Get hotspot name and password
```c++
SOFTAPMANAGER->getSsid();
SOFTAPMANAGER->getPwd();
```
Registration and un-registration hotspot status monitoring
```c++
void addSoftApStateListener(ISoftApStateListener *pListener);
void removeSoftApStateListener(ISoftApStateListener *pListener);
```