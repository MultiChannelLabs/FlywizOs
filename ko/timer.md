# <span id = "timer">타이머</span>
 어떤 경우에는 정기적으로 특정 작업을 수행해야 할 수도 있습니다. 예를 들어, 정기적으로 하트 비트 패킷을 보내거나, 정기적으로 데이터를 쿼리하여 UI를 새로 고치거나, 몇 가지 폴링 작업을 수행합니다. 이러한 요구 사항이 있는 경우는 타이머가 좋은 선택입니다.

## 타이머 사용법
1. 타이머 
     사용 편의성을 위해 구조체를 채우는 형태로 타이머를 추가합니다.
 Logic.cc 파일에는 기본적으로 다음과 같은 구조체 배열이 있습니다.
     
    ```c++
    /**
     * Register timer
     * Just add to this array
     */
    static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
    //{0,  6000}, //Timer id=0, Period 6second
    //{1,  1000},
    };
    ```
     타이머를 추가하려면 이 구조체 배열에 값을 추가하기 만 하면됩니다.
     이 구조체의 정의는 다음과 같습니다.
    
    ```c++
typedef struct {
int id; // Timer ID, can not redefine
int time; // Timer period unit/ms
}S_ACTIVITY_TIMEER;
    ```

2. 타이머 로직 코드 추가  
    배열에 타이머를 등록한 후 타이머가 트리거되면 시스템은 해당 **Logic.cc** 파일에서 `void onUI_Timer (int id)`함수를 호출합니다. 이 타이머의 모든 작업 코드는 다음과 같습니다. 이 함수에 필요한 코드를 추가하십시오.

   ```c++
   /**
    * Timer trigger function
    * It is not recommended to write time-consuming operations in this function, otherwise it will affect UI refresh
    * @param id
    *         The id of the currently triggered timer is the same as the id at registration
    * @return true
    *             Keep running the current timer
    *         false
    *             Stop running the current timer
    */
   static bool onUI_Timer(int id){
    switch (id) {
   
   	default:
   		break;
    }
     return true;
   }
   ```

    이 함수는 기본적으로 **Logic.cc** 파일에 생성됩니다.
    구조체 배열에 정의 된 **id** 값과 함수의 파라미터 **id**는 동일하며, **id** 값에 따라 필요한 조작을 할 수 있습니다.

> [!Note]
> **참고 : 각 액티비티의 타이머는 독립적이며 다른 액티비티의 타이머 ID는 동일 할 수 있습니다. **
> **액티비티가 파괴되지 않는 한 등록 된 타이머 ([액티비티 라이프 사이클](activity_life_cycle.md) 참조) 는 항상 실행됩니다. **
> **등록 후 수동으로 중지 할 필요가 없으며 액티비티가 종료되면 자동으로 중지됩니다. **

##  예제
 다음으로 구체적인 예를 들어 타이머 사용을 설명하겠습니다.
 정수 변수가 있고 매초 1씩 증가하여 결과를 화면에 표시하는 함수를 구현해야한다고 가정 해 보겠습니다.
 구체적인 구현 프로세스는 다음과 같습니다.

1. 먼저 UI 파일에 Text View 컨트롤을 추가하여 누적 된 결과를 표시합니다.

    ![](assets/timer/example_text.png)  
2. 타이머를 등록하고 **mainLogic.cc**의 타이머 배열에 구조를 추가합니다. 타이머 ID는 1이고 시간 간격은 1 초입니다. 시간 단위는 ms입니다.

    ![](assets/timer/example_struct.png)
    
3. **mainLogic.cc**에서 정적 정수 변수를 정의하고 0으로 초기화합니다.
   
    ![](assets/timer/example_cout.png)  
4. `void onUI_Timer (int id)`함수에서 증가 코드를 추가하고 Text View 컨트롤에 표시합니다.
   
    ![](assets/timer/example_timer.png)
5. 컴파일 후 다운로드하여 실행합니다.   
   
    ![](assets/timer/example_preview.png)  

## Sample code  
 더 자세한 내용은 [Sample Code](demo_download.md#demo_download)의 `TimerDemo` 프로젝트를 참고하십시오.

