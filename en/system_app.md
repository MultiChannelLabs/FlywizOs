# System activity type
The application activity introduced above is classified as a normal window, which is usually enough. When creating a new UI activity through the tool, the default window type is normal window：  

 ![](images/5939b5202b235b3a3e0c9d773f749b26_597x852.png)

If some scenes require a display area floating above the UI interface, then ordinary windows will not be able to do the job, and we need to use several other types of windows.
In the **UI type** options, there are three special types of window options, these three special types have special file names, corresponding to

* **statusbar.ftu**
* **navibar.ftu**
* **screensaver.ftu**  

  ![](images/screenshot_1512460753534.png)

After clicking Finish, the tool will automatically generate the corresponding code for us; the operations of these three types of windows are the same as those of ordinary windows;

## Status bar
Explanation: This status bar has the same concept as the status bar of Android and iOS phones. It is a general display area floating above the UI interface. Usually used to display some common information, or to place the return button or home button, etc. 

The following effects:
![](assets/statusbar.png)

The system provides two interfaces that can be used to operate the status bar:

Show status bar：
```c++
EASYUICONTEXT->showStatusBar();
```
Hide status bar：
```c++
EASYUICONTEXT->hideStatusBar();
```
For the complete source code, please refer to the **StatusBarDemo** project in [**Sample Code Package**](demo_download.md#demo_download)

## Navigation bar
Explanation: This navigation bar has the same concept as the navigation bar of Android phones. It is a general operation or display area floating above the UI interface, generally at the bottom of the page. Usually used to display some operation keys. The navigation bar is actually no different from the status bar.

Show navigation bar：
```c++
EASYUICONTEXT->showNaviBar();
```
Hide navigation bar：
```c++
EASYUICONTEXT->hideNaviBar();
```

## Screensaver
Explanation: The screensaver means that when the user no longer interacts with the system and the time exceeds a specified length of time then the system automatically opens a page.
Right-click the project, select the Properties option, in the pop-up properties box, we can set the screensaver timeout time, the unit is seconds, -1 means not enter the screensaver.
We can also make some settings through code, see jni/include/entry/EasyUIContext.h :

* Required header file
 ```c++
 #include "entry/EasyUIContext.h"
 ```

* Set screensaver timeout time
```c++
//Set the screensaver timeout time to 5 seconds
EASYUICONTEXT->setScreensaverTimeOut(5); 
```

* Set whether to allow screensaver

  ```c++
  EASYUICONTEXT->setScreensaverEnable(false); //Turn off screensaver detection
  EASYUICONTEXT->setScreensaverEnable(true); //Turn on screensaver detection
  ```
  > Application scenario: If the upgrade interface cannot enter the screensaver mode, you can turn off the screensaver detection in the upgrade application EASYUICONTEXT->setScreensaverEnable(false).
  
* Enter the screensaver
```c++
EASYUICONTEXT->screensaverOn();
```

* Exit the screensaver
```c++
EASYUICONTEXT->screensaverOff();
```

* Determine whether to enter the screensaver
```c++
EASYUICONTEXT->isScreensaverOn();
```

The complete source code can be found in the **ScreensaverDemo** project in [**Sample Code Package**](demo_download.md#demo_download)
