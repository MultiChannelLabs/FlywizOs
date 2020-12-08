# Hotspot設定アクティビティ開始
```c++
EASYUICONTEXT->openActivity("SoftApSettingActivity");
```
# Hotspot動作関数の説明
SoftApManagerオブジェクトの読み込み
```c++
#include "net/NetManager.h"
SoftApManager *pSAM = NETMANAGER->getSoftApManager();

// You can define a macro to facilitate the following functino calls
#define SOFTAPMANAGER     NETMANAGER->getSoftApManager()
```
Hotspotオン
```c++
SOFTAPMANAGER->setEnable(true);
```
Hotspotがオンであることを確認し
```c++
SOFTAPMANAGER->isEnable();
```
現在hotspotの状態を取得
```c++
SOFTAPMANAGER->getSoftApState();

// There are the following states
E_SOFTAP_DISABLED	// Disabled
E_SOFTAP_ENABLING	// During tunning on
E_SOFTAP_ENABLED	// Turn on successfully
E_SOFTAP_DISABLING // During tunning off
E_SOFTAP_ENABLE_ERROR	// Turn on failed
```
Hotspot名前とパスワードを設定
```c++
SOFTAPMANAGER->setSsidAndPwd("zkswe", "abcd1234");
```
Hotspot名前とパスワードを取得する
```c++
SOFTAPMANAGER->getSsid();
SOFTAPMANAGER->getPwd();
```
Hotspot状態監視機能の登録と解除
```c++
void addSoftApStateListener(ISoftApStateListener *pListener);
void removeSoftApStateListener(ISoftApStateListener *pListener);
```