## Open the wifi setting activity
```c++
EASYUICONTEXT->openActivity("WifiSettingActivity");
```

## wifi operation function description
Get WifiManager object
```c++
#include "net/NetManager.h"
WifiManager *pWM = NETMANAGER->getWifiManager();

// You can define a macro to facilitate the following function calls
#define  WIFIMANAGER    NETMANAGER->getWifiManager()
```
Check whether the machine supports wifi
```c++
WIFIMANAGER->isSupported();
```
Check if wifi is on
```c++
WIFIMANAGER->isWifiEnable();
```
Turn on wifi
```c++
WIFIMANAGER->enableWifi(true);
```
Scan wifi
```c++
WIFIMANAGER->startScan();
```
Connect to wifi
```c++
WIFIMANAGER->connect(ssid, pw);
```
Disconnect wifi connection
```c++
WIFIMANAGER->disconnect();
```
Check if wifi is connected
```c++
WIFIMANAGER->isConnected();
```
Get connected wifi information
```c++
WIFIMANAGER->getConnectionInfo();
```
Registration and un-registration wifi information monitoring
```c++
void addWifiListener(IWifiListener *pListener);
void removeWifiListener(IWifiListener *pListener);
```
## Sample code  
See the `NetDemo` project in [Sample Code](demo_download.md#demo_download)