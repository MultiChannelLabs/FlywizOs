# 스크린샷
제품 개발 후 매뉴얼 작성시 실행중인 인터페이스의 스크린샷이 필요할 수 있으며, 아래 스크린샷 코드를 참고하십시오.
## Ready
1. [screenshot.h](https://docs.flythings.cn/src/screenshot.h) 소스 파일을 다운로드하여 프로젝트`jni` 디렉토리에 저장합니다. 
    ![](assets/screenshot1.png)

## Use

* 필요한 헤더 파일
  ```c++
  #include "screenshot.h"
  ```
* 함수를 호출하여 스크린샷 찍기
  ```c++
  static bool onButtonClick_Button1(ZKButton *pButton) {
    //Capture the current screen, save it as a bmp picture, and save it to the TF card directory
    //Each time this function is called, the name of the saved picture is incremented
    //Example - screenshot01.bmp、screenshot02.bmp、screenshot03.bmp
    Screenshot::AutoSave();
    return false;
  }
  ```
  사진은 기본적으로 TF카드에 저장되므로 TF 카드를 장착하고 스크린샷을 찍으십시오.
  다른 위치에 저장해야하는 경우 소스 코드를 직접 수정할 수 있습니다. 
