
# FAQ
* ### Time-consuming operations in the UI main thread cause the card to not display the upgrade interface
The refresh display of the activity is handled in the main UI thread. If there are some time-consuming operations or an infinite loop of the program in the main UI thread, it will affect the refresh of the UI and cause the card to not display the upgrade interface;
`onUI_init`, `onUI_intent`, `onUI_show`, `onUI_hide`, `onUI_quit`, `onUI_Timer` and some callback interfaces related to controls, these functions are all called in the UI main thread, so this situation should First check if there are any time-consuming operations in these functions;
In this case, the machine can only be restarted by plugging in the card. After the system is up, it will first check whether it needs to be upgraded, so that the upgrade interface can be displayed normally.

* ### Unable to download and debug/download and debug failed
  First confirm that the computer and the screen are connected correctly. If it is a screen with WIFI, it only supports WIFI connection and cannot use the USB cable connection; similarly, if it is a screen without WIFI, then it can only be connected via a USB cable, if it is connected by USB Normally, the computer will recognize it as a USB device.  
  After confirming the supported connection mode, go to the development tool menu bar, select **Debug Configuration -> ADB Configuration**, set the corresponding connection mode, and save.  
  Try to download again.   
  [How to download and debug via ADB](adb_debug.md)
  
* ### The program suddenly restarts by itself or gets stuck  
  First, when an unexpected situation occurs in the program, you must check the log ([How to view the log](logcat.md)), try to reproduce the problem repeatedly, and determine the problem code based on the log.  
  If the program crashes and restarts, a similar log will generally appear on the log. These logs will be output when the program is started and initialized, so you can use this to determine whether the program has restarted. 
  
  ![](assets/start_log.png)  
  
  Most of the causes of program crashes can be attributed to incorrect usage of pointers. E.g  
  * Null pointer
  * Array out of bounds
  * Did not pay attention to the life cycle of the pointer, but the memory is still in use after the release 
  
  etc.  
  Since the project uses C and C++ language programming, it is inevitable that we need to deal with raw pointers in terms of pointer memory, which requires us to be extra careful.
  There is another kind of crash, which may be caused by not paying attention to the error of **Divisor cannot be 0**.
  
  If the program is stuck, from the log, there is no restart phenomenon, then we can check from **thread deadlock**, **whether the code loops indefinitely**, **there is a long time-consuming operation, causing the stuck the illusion of death** analyze these situations.