# 밝기 조절
* 필요한 헤더 파일
  ```c++
  #include "utils/BrightnessHelper.h"
  ```
  
## Dimming
* 스크린 밝기 조절 
  밝기의 범위는 **0 ~ 100**입니다. (Note : 0은 스크린이 꺼지는 것을 의미하지 않습니다)
  
  ```c++
  //Adjust the screen brightness to 80
  BRIGHTNESSHELPER->setBrightness(80);
  ```
* 현재 밝기 값 가져오기
  ```c++
  BRIGHTNESSHELPER->getBrightness();
  ```
  
## 스크린 온/오프

* 스크린 끄기
    ```c++
    BRIGHTNESSHELPER->screenOff();
    ```
* 스크린 켜기
    ```c++
    BRIGHTNESSHELPER->screenOn();
    ```

## 밝기 값 저장
시스템이 시작되면 스크린은 마지막으로 조정된 밝기 값을 기본으로 설정됩니다. 만약 밝기 값을 저장하고 싶지 않다면 프로젝트의 프로퍼티에서 이를 변경 할 수 있습니다.
![](images/property_brightness.png)