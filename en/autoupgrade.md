# Automatic card upgrade(插卡自动升级)
In the case of screen damage or inaccurate touch, if we want to upgrade the system, we can create a file in the root directory of the TF card

(在屏幕损坏或触摸不准情况下，想要对系统进行升级，我们可以在TF卡根目录下创建一个文件)
**zkautoupgrade** (Note: The file has no suffix)（注意：该文件是没有后缀名的）  

![](images/Screenshotfrom2018-06-07195801.png)

In this way, the machine will automatically check the upgrade item after the card is inserted, and the upgrade will start after 2 seconds by default; if you need to control the time before the upgrade, we can open the `zkautoupgrade` file and fill in the corresponding number, the unit is seconds; after the upgrade is completed , The system restarts, remember to pull out the TF card to prevent automatic upgrade again.

(这样机器插卡后会自动勾选上升级项，默认2s后开始升级；如果需要控制其他时间后才开始升级，我们可以打开`zkautoupgrade`文件填相应的数字即可，单位为秒；升级完成后，系统重启，记得要拔出TF卡，防止再次自动升级。)