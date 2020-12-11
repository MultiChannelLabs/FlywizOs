
# <span id = "ftu_and_source_relationships">FlywizOS의 컴파일 과정과 UI파일 및 소스 코드의 상관 관계</span>
## UI파일의 컨트롤이 포인터 변수와 연결되는 방식
FlywizOS는 간편한 관리를 위해 UI와 code를 분리했습니다.  
아래 그림에서, UI파일은 프로젝트의 UI폴더의 모든 ftu파일들입니다.  
개발하는 동안 코드의 중복을 줄이기 위해서, FlywizOS IDE는 컴파일 과정을 개선했습니다. 실제 소스 코드를 컴파일 하기 전에, IDE는 먼저 UI파일로부터 생성된 동일한 접두사 이름을 가지는 `Logic.cc`파일을 생성합니다.(예 : `main.ftu`는 `mainLogic.cc`파일이 생성됨). 여기서 `Logic.cc`파일의 생성은 바로  덮어써지는 것이 아니라, 점차적으로 수정된다는 것에 주의해야 합니다.  
컴파일 시, IDE는 각 Ui파일을 순회하며 UI파일에 포함된 컨트롤을 읽어 코드에 컨트롤을 위한 포인터 변수를 정의하고, 개발자는 이 포인터를 이용하여 해당하는 컨트롤을 제어할 수 있습니다. 이 포인터 변수들은 UI파일과 동일한 접두사 이름을 가지는 `Activity.cpp` 파일 안에 정의됩니다. **main.ftu**를 예로 들면, 아래와 같습니다.

![](assets/global_control_pointer.png)  

**위의 그림에서 보는 것처럼 모든 포인터들은 static global변수들입니다. 그리고, 그것들은 모두 동일한 이름 지정 규칙에 의해 생성되었습니다. 이 이름 지정 규칙은 [컨트롤의 ID를 기반으로 한 포인터 변수의 이름 지정 규칙](named_rule.md#id_name_rule)을 참고하십시오. 그리고 위 그림에서 `#include "logic/mainLogic.cc"`도 주의해야 할 부분으로,  `mainLogic.cc`은 `mainActivity.cpp`에 포함되고, 개발자는 `mainLogic.cc`에서 필요한 코딩을 하기에 모든 컨트롤 포인터 변수를 사용할 수 있습니다.**  
만약 이 포인터들의 초기화에 관심이 있다면 `mainActivity`의  `onCreate` 함수를 찾아보십시오.

## UI파일들과 Logic.cc파일들 사이의 관계
위에서 우리는 UI파일의 컨트롤이 어떻게 포인터 변수와 연결되는지에 대해서 알아보았습니다. 이제는 `mainLogic.cc`파일에 어떤 것들이 자동으로 생성되는지 알아보겠습니다.
만약 UI파일에 아무런 컨트롤도 추가하지 않았다면 `mainLogic.cc`파일은 아래와 같습니다.

```c++ 
/**
 * Register timer
 * Fill the array to register the timer
 * Note: id cannot be repeated
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //Timer id=0, period 6 second
	//{1,  1000},
};

/**
 * Triggered when the interface is constructed
 */
static void onUI_init(){
    //Add the UI initialization display code here, for example :
    //mText1Ptr->setText("123");

}

/**
 * Triggered when switching to this interface
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * Triggered when the interface is displayed
 */
static void onUI_show() {

}

/*
 * Triggered when the interface is hidden
 */
static void onUI_hide() {

}

/*
 * Triggered when the interface completely exits
 */
static void onUI_quit() {

}

/**
 * Serial data callback interface
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * Timer trigger function
 * It is not recommended to write time-consuming operations in this function, otherwise it will affect UI refresh
 * Parameter : id
 *         The id of the currently triggered timer is the same as the id at registration
 * Return : true
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

/**
 * Triggered when there is a new touch event
 * Parameter : ev
 *         new touch event
 * Return : true
 *            Indicates that the touch event is intercepted here, and the system will no longer pass this touch event to the control
 *         false
 *            Touch events will continue to be passed to the control
 */
static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://Touch press
//			LOGD("event time = %ld axis  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://Touch move
			break;
		case MotionEvent::E_ACTION_UP:  //Touch up
			break;
		default:
			break;
	}
	return false;
}
```

 아래는 각 함수들에 대한 설명입니다.
* **REGISTER_ACTIVITY_TIMER_TAB[ ]  array**  
  [타이머 등록](timer.md#timer)에 사용됩니다. 이 구조체 배열은 아래와 같습니다.
  ```c++
  typedef struct {
      int id; // Timer ID, cannot be repeated
      int time; // Timer interval, unit millisecond
  }S_ACTIVITY_TIMEER;
  ```
  **본질적으로, 이 배열은 `void registerTimer(int id, int time)`함수에 의해 시스템에 등록되고, `mainActivity.cpp`의 `rigesterActivityTimer()`함수에서 참조될 것입니다.**

* **void onUI_init()**  
  액티비티의 초기화에 사용됩니다. 만약 UI 액티비티의 시작 시 초기화가 필요한 컨텐츠가 있다면 이 함수에 코드를 추가할 수 있습니다.  
  이 함수는 `mainActivity.cpp`의 `onCreate()`함수에서 호출됩니다. 

* **void onUI_quit()**  
  액티비티의 종료에 사용됩니다. 만약 UI 액티비티 종료 시 어떤 작업이 필요하다면, 이 함수에 코드를 추가할 수 있습니다.  
  이 함수는 `mainActivity.cpp`의 파괴자에서 호출됩니다.

* **void onProtocolDataUpdate(const SProtocolData &data)**  
  시리얼 포트 데이터를 받는데 사용됩니다. 시리얼 데이터 프레임이 분석된 후 이 함수가 호출됩니다.  
  이 함수는 `mainActivity.cpp`의 `onCreate()`에서 `void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener)`를 통해 등록되고, `mainActivity.cpp`의 파괴자에서 등록 해제됩니다. 더 자세한 사항은 [시리얼 프레임웍](serial_framework.md)을 참고하십시오.

* **bool onUI_Timer(int id)**  
  타이머 콜백 함수입니다. 등록된 타이머의 타이머 주기가 도달했을 때, 시스템에 의해 호출됩니다. 타이머가 여러 개 등록되었었다면, id파라미터로 각 타이머를 구분할 수 있습니다. 이 id는 **REGISTER_ACTIVITY_TIMER_TAB[] array**에 등록된 id와 같습니다.  
  Return `true`  해당 타이머를 계속 유지합니다.  
  Return `false` 해당 타이머를 중지합니다.  
  `false`를 반환하여 타이머를 중지했다면 어떻게 다시 시작합니까?[타이머를 임의로 시작 및 중지하는 방법](how_to_register_timer.md)을 참조하십시오.

* **bool onmainActivityTouchEvent(const MotionEvent &ev)**  
  터치 이벤트 콜백 함수입니다. 모든 터치 메세지를 수신 가능합니다.  
  유사하게 `mainActivity.cpp`의 `registerGlobalTouchListener`를 통해 등록되며, 등록이 완료된 이후에야 터치 이벤트가 수신됩니다.  
  Return `true` 터치 이벤트가 더이상 다른 컨트롤로 전달되지 않습니다.  
  Return `false` 터치 이벤트가 지속적으로 다른 컨트롤로 전달됩니다.  
  [터치 이벤트 처리에 대한 이해](motion_event.md)를 참고하십시오.

이상은 기본 UI파일이 컴파일 될 때 자동으로 Logic.cc에 생성됩니다. UI파일에 컨트롤을 추가하고 컴파일을 한다면, IDE는 해당하는 Logic.cc에 각각의 컨트롤과 관련된 함수들을 자동을 생성할 것입니다.   
예를 들어, **main.ftu** UI 파일에 두 개의 버튼 컨트롤을 추가하고, 각가의 ID를 `Button1`과 `Button2`로 만들어 컴파일하면, 아래의 2개 함수가 **mainLogic.cc**파일에 생성됩니다.
```c++
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}
```
함수의 이름에 주목하십시오. 함수의 이름은 컨트롤의 ID를 포함하고 있어, 컨트롤의 ID는 C언어의 네이밍 표준을 준수해야 합니다. 만약 계속적으로 컨트롤을 추가한다면, 추가된 컨트롤과 관련된 함수들은 컴파일 후에 **mainLogic.cc**에 생성됩니다.  

일반적으로 개발하는 동안, UI파일에서 컨트롤의 추가/삭제/수정이 매우 빈번히 일어나는데, 이러한 상황에서 IDE는 아래와 같이 동작합니다.   
* 컨트롤을 추가하는 경우 - IDE는 컴파일 시 컨트롤의 ID를 기반으로하여 관련된 함수를 생성하는데, 만약 동일한 함수가 이미 존재한다면, 그 과정을 건너뛰어지고, **Logic.cc**파일도 변경되지 않습니다.
* 컨트롤을 삭제하는 경우 - UI파일에 존재하는 컨트롤을 삭제하더라도 관련된 함수는 계속적으로 존재합니다. 만약 관련 함수 역시 삭제된다면, 의도하지 않은 코드의 손실이 발생할 수 있어 FlywizOS IDE에서는 삭제하지 않는 것으로 결정했습니다.
* 컨트롤을 수정하는 경우 - 생성된 컨트롤 관련 함수는 오직 컨트롤의 ID와만 관련이 있습니다. 만약 Ui파일에서 컨트롤의 ID 이외의 속성을 수정한다면 이는 관련 함수에는 영향을 미치지 않습니다. 만약 컨트롤의 ID를 수정 후 컴파일을 한다면, 새롭게 컨트롤을 추가하는 것과 동일한 과정이 진행되고, 기존 생성되었던 관련 함수는 유지됩니다.

**이 장에서는 오직 버튼 컨트롤과 관련된 예제로 UI파일의 컨트롤과 Logic.cc에 생성된 관련 함수의 관계에 대해서만 설명하였습니다. FlywizOS는 또한 다른 컨트롤(예 : Slide Bar, List, Slide Windows등) 에 대해서도 관련된 함수를 제공합니다. 더 자세히 다른 컨트롤과 관련된 함수에 대해 알고 싶다면 [컨트롤에 의해 자동으로 생성된 함수들의 관계에 대한 설명](named_rule.md#relation_function)을 참고하십시오.**  

**끝으로, 아래의 그림은 ftu파일과 코드 사이의 상관 관계에 대한 간략한 그림입니다.**
![](assets/relationships.png)