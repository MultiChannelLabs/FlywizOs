 開発者が直接作成されたアクティビティに加えて、システムで提供されているいくつかの組み込みアクティビティがあります。たとえばTFカードを利用してシステムを更新時に自動的に実行されている内蔵アクティビティがあります。

![](images/boot_logo_upgrade.jpg)

 加えて、設定アクティビティがあり、以下の方法で実行します。
```c++
EASYUICONTEXT->openActivity("ZKSettingActivity");
```
 私たちは、ボタンなどを利用して設定アクティビティを実行することができます。（他のいくつかの内蔵アクティビティもこの方法で実行が可能です。）:
```c++
static bool onButtonClick_Button1(ZKButton *pButton) {
    EASYUICONTEXT->openActivity("ZKSettingActivity");
    return false;
}
```
![](images/setup_setting.jpg)

 それぞれのアイテムが選択されると、それぞれ内蔵された他のアクティビティが実行されます。まず、** Network**を選択します。
```c++
EASYUICONTEXT->openActivity("NetSettingActivity");
```
![](images/net_setting.jpg)

 **WIFI** 設定:
```c++
EASYUICONTEXT->openActivity("WifiSettingActivity");
```
![](images/wifi_setup.jpg)

 If your board supports WIFI, the WIFI will be displayed in the activity when you activate the WIFI on button on the upper right.

 **Hotspot** 設定:
```c++
EASYUICONTEXT->openActivity("SoftApSettingActivity");
```
![](images/soft_ap_setup.jpg)

**Language** 設定:

```c++
EASYUICONTEXT->openActivity("LanguageSettingActivity");
```
![](images/lang_setting.jpg)

**Touch calibration** 設定:
```c++
EASYUICONTEXT->openActivity("TouchCalibrationActivity");
```
![](images/touchcalibration.png)

**Developer options** 設定:
```c++
EASYUICONTEXT->openActivity("DeveloperSettingActivity");
```
![](images/developer_setting.jpg)

現在は、唯一のADBデバッグの設定が可能です。
