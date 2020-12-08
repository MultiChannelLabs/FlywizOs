## WIFI設定アクティビティ開始
```c++
EASYUICONTEXT->openActivity("WifiSettingActivity");
```

## WiFi動作関数の説明
WifiManager 객체 가져오기
```c++
#include "net/NetManager.h"
WifiManager *pWM = NETMANAGER->getWifiManager();

// You can define a macro to facilitate the following function calls
#define  WIFIMANAGER    NETMANAGER->getWifiManager()
```
機器がWIFIをサポートすることを確認
```c++
WIFIMANAGER->isSupported();
```
WIFIがOnであることを確認し
```c++
WIFIMANAGER->isWifiEnable();
```
WIFIオン
```c++
WIFIMANAGER->enableWifi(true);
```
WIFI検索
```c++
WIFIMANAGER->startScan();
```
WIFI接続
```c++
WIFIMANAGER->connect(ssid, pw);
```
WIFI接続を解除
```c++
WIFIMANAGER->disconnect();
```
WIFIが接続されて
```c++
WIFIMANAGER->isConnected();
```
接続されたWIFI情報を取得する
```c++
WIFIMANAGER->getConnectionInfo();
```
WIFI情報監視機能の登録および登録解除
```c++
void addWifiListener(IWifiListener *pListener);
void removeWifiListener(IWifiListener *pListener);
```
## Sample code  
詳細については、[Sample Code](demo_download.md＃demo_download)の`NetDemo`プロジェクトを参照してください。