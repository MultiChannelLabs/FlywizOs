
# View log
## Log 추가
* 필요한 헤더 파일
  ```c++
  #include "utils/Log.h"
  ```
  FlywizOS는 `LOGD`또는 `LOGE`매크로를 통해 로그를 출력합니다. 사용 방법은 C언어의 `printf`와 같습니다. 
아래는 자동적으로 생성된 코드에 있는 예제입니다.
  
    ```c++
    static bool onButtonClick_Button1(ZKButton *pButton) {
        LOGD("onButtonClick_Button1\n");
        return true;
    }
    ```

## 로그 확인

[ADB](adb_debug.md) 연결 후, 툴을 통해 프로그램에 있는 로그를 확인할 수 있습니다. 방법은 아래와 같습니다.

1. 메뉴에서 **FlywizOS** -> **Show Log Perspective**를 선택하면 IDE는 다른 화면으로 전환됩니다.
    ![](assets/ide/log_perspective.png)

2. 새로운 화면의 왼쪽 아래에서 **LogCat**을 선택합니다. 만약 정상이라면 오른쪽의 빨간 색 박스 영역에서 출력되는 로그를 확인할 수 있습니다.
    ![](assets/ide/log_view.png)   
    만약 코딩 화면으로 다시 전환하고 싶다면 IDE의 우측 상단 코너의 **FlywizOS** 아이콘을 클릭하십시오.
    ![](assets/ide/perspective_fly.png)