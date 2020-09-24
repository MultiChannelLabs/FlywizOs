In addition to the activity customized by the developer, our system also has several commonly used activity built in, such as the activity that appears when the card is upgraded, which is one of the built-in activity ;
![](images/boot_logo_upgrade.jpg)

In addition, there is a system setting activity, open method :
```c++
EASYUICONTEXT->openActivity("ZKSettingActivity");
```
We can click on a button to jump to this activity to see the effect (the effects of several other built-in interfaces can be viewed in the following ways) :
```c++
static bool onButtonClick_Button1(ZKButton *pButton) {
    EASYUICONTEXT->openActivity("ZKSettingActivity");
    return false;
}
```
![](images/setup_setting.jpg)

After each item is clicked in, there is a new built-in activity, open the network settings :
```c++
EASYUICONTEXT->openActivity("NetSettingActivity");
```
![](images/net_setting.jpg)

Open WIFI settings :
```c++
EASYUICONTEXT->openActivity("WifiSettingActivity");
```
![](images/wifi_setup.jpg)

If the target machine supports wifi, turn on the switch in the upper right corner, the searched wifi information will be displayed on the activity;

Open the hotspot setting activity:
```c++
EASYUICONTEXT->openActivity("SoftApSettingActivity");
```
![](images/soft_ap_setup.jpg)

Back to the system setting activity just now, we click to open the language setting activity:
```c++
EASYUICONTEXT->openActivity("LanguageSettingActivity");
```
![](images/lang_setting.jpg)

Touch calibration interface:
```c++
EASYUICONTEXT->openActivity("TouchCalibrationActivity");
```
![](images/touchcalibration.png)

Developer options activity :
```c++
EASYUICONTEXT->openActivity("DeveloperSettingActivity");
```
![](images/developer_setting.jpg)

Currently there are only ADB debugging switch options.
