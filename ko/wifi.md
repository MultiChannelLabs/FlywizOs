## WIFI 설정 액티비티 시작
```c++
EASYUICONTEXT->openActivity("WifiSettingActivity");
```

## WiFi 작동 함수 설명
WifiManager 객체 가져오기
```c++
#include "net/NetManager.h"
WifiManager *pWM = NETMANAGER->getWifiManager();

// You can define a macro to facilitate the following function calls
#define  WIFIMANAGER    NETMANAGER->getWifiManager()
```
기기가 WIFI를 지원하는지 확인
```c++
WIFIMANAGER->isSupported();
```
WIFI가 On인지 확인
```c++
WIFIMANAGER->isWifiEnable();
```
WIFI 켜기
```c++
WIFIMANAGER->enableWifi(true);
```
WIFI 검색
```c++
WIFIMANAGER->startScan();
```
WIFI 연결
```c++
WIFIMANAGER->connect(ssid, pw);
```
WIFI 연결 해제
```c++
WIFIMANAGER->disconnect();
```
WIFI가 연결되었는지 확인
```c++
WIFIMANAGER->isConnected();
```
연결된 WIFI 정보 가져오기
```c++
WIFIMANAGER->getConnectionInfo();
```
WIFI정보 모니터링 함수 등록 및 등록해제
```c++
void addWifiListener(IWifiListener *pListener);
void removeWifiListener(IWifiListener *pListener);
```
## Sample code  
더 자세한 내용은 [Sample Code](demo_download.md#demo_download)의 `NetDemo` 프로젝트를 참고하세요.