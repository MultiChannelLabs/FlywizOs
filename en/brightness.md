# Screen backlight operation(屏幕背光操作)
* Required header files(所需头文件  )
  ```c++
  #include "utils/BrightnessHelper.h"
  ```
  
## Dimming(亮度调节)
* Adjust backlight brightness(调节背光亮度)  
  The brightness range is **0 ~ 100** (Note: 0 does not mean turning off the screen)(亮度范围是 **0 ~ 100**   (注意：0并不等于关屏)  )
  
  ```c++
  //Adjust the screen brightness to 80(将屏幕亮度调整为80)
  BRIGHTNESSHELPER->setBrightness(80);
  ```
* Get the current brightness value(获取当前亮度值)
  ```c++
  BRIGHTNESSHELPER->getBrightness();
  ```
  
## Switch screen backlight(开关屏幕背光)

* Screen off(关屏)
    ```c++
    BRIGHTNESSHELPER->screenOff();
    ```
* Screen on(开屏)
    ```c++
    BRIGHTNESSHELPER->screenOn();
    ```

## Memory brightness(记忆亮度)
When the system is turned on, the default is to memorize the last adjusted brightness value. If you want to modify it to not remember the brightness or set a fixed brightness value, you can open the properties of the project to modify(系统开机起来默认是记忆最后调节的亮度值，如果想要修改为不记忆亮度或设置固定的亮度值，可以打开工程的属性进行修改)：  

  ![](images/property_brightness.png)