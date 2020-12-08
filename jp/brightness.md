# 明るさの調整
* 必要なヘッダファイル
  ```c++
  #include "utils/BrightnessHelper.h"
  ```
  
## Dimming
* スクリーンの明るさの調整
  明るさの範囲は、**0〜100**です。（Note：0このスクリーンがオフを意味しません）
  
  ```c++
  //Adjust the screen brightness to 80
  BRIGHTNESSHELPER->setBrightness(80);
  ```
* 現在の明るさの値を取得する
  ```c++
  BRIGHTNESSHELPER->getBrightness();
  ```
  
## スクリーンオン/オフ

* スクリーンオン
    ```c++
    BRIGHTNESSHELPER->screenOff();
    ```
* スクリーンオフ
    ```c++
    BRIGHTNESSHELPER->screenOn();
    ```

## 明るさの値を保存
システムが起動されると、スクリーンは、最後に調整された明るさの値を基に設定されます。もし明るさの値を保存したくない場合は、プロジェクトのプロパティで、これを変更することができます。
![](images/property_brightness.png)