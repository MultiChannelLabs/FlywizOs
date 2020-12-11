# 액티비티 활동 주기
액티비티 활동 주기를 소개하기 전에 먼저 액티비티 간의 계층 관계에 대해 알아보겠습니다.   
![](images/activity_hierarchy.png)

 FlywizOS의 어플리케이션은 가장 먼저 **mainActivity**라는 시작 액티비티가 실행되고, `openActivity`함수를 통해 **subActivity**, **thirdActivity**를 실행할 수 있습니다. 위 그림은 액티비티 간의 관계를 나타내고 있으며, 그림처럼 액티비티가 저장되는 스택이 있고, 이 스택에 **mainActivity**부터 나중에 실행된 액티비티가 기존 액티비티 위에 쌓이는 형태로 구성됩니다.

## 액티비티 실행 과정
`openActivity`함수를 호출 한 후의 과정을 살펴 보겠습니다. 두 가지 경우가 있습니다.

1. 액티비티 스택에 실행하려는 액티비티가 없는 경우
   ![](images/openactivity_exist.png)

    **subLogic.cc**의 `onUI_init`함수를 살펴 보겠습니다. 액티비티 스택에 액티비티가 없는 경우에 이 함수가 사용됩니다. 이 함수가 호출되었다는 것은 모든 컨트롤 포인터가 초기화가 완료되었음을 의미합니다. 이 함수에서는 다음과 같이 몇 가지 작업을 수행 할 수 있습니다.

   ```c++
   static void onUI_init() {
     //Tips :Add the display code of UI initialization here, such as:mTextView1Ptr->setText("123");
     LOGD("sub onUI_init\n");
     mTextView1Ptr->setText("123");
   }
   ```
   만약 초기화 시 사용자가 특정한 데이터를 전달하고 싶다면 `onUI_intent` 함수로 그 데이터를 전달받을 수 있습니다.
   ```c++
   static void onUI_intent(const Intent *intentPtr) {
     LOGD("sub onUI_intent\n");
     // Judge not empty
     if (intentPtr) {
   	 // Key value analysis
   	 std::string cmd = intentPtr->getExtra("cmd");		// "open"
   	 std::string value = intentPtr->getExtra("value");	// "ok"
   	 ......
     }
   }
   ```
    `onUI_show` 함수 - 액티비티 디스플레이 완료 콜백 함수

2. 액티비티 스택에 실행하려는 액티비티가 존재하는 경우
   ![](images/openactivity_movetotop.png)

   이 경우 해당하는 액티비티가 액티비티 스택의 최상위로 이동되며, ~~`onUI_init`~~함수는 호출되지 않습니다.   
   ![](images/openactivity_notexist.png)

   실행되는 액티비티가 디스플레이되면 직전 최상위 액티비티는 숨겨집니다.   
   아래는 **mainActivity**에서 **subActivity**가 실행될 때의 과정을 보여줍니다.
   ![](images/activity_pause_and_resume.png)

   이 과정에서 중요하게 여길 부분은  **mainActivity** **hide** ------> **subActivity** **display** 입니다.

## 액티비티 종료 과정
액티비티를 종료하는 방법에는 3가지의 방법이 있습니다.
1. `goBack()` - 최상위 액티비티를 즉시 종료합니다.
   ![](images/activity_goback.png)

   액티비티가 종료될 때 `onUI_quit`함수가 호출되며, 만약 해제가 필요한 리소스들이 있다면 이 함수에서 해제하는 것을 권장합니다.
   ![](images/activity_ui_quit.png)

   최상위 액티비티가 종료된 후 다음 액티비티의 `onUI_show`함수가 호출되고 액티비티가 디스플레이됩니다.

2. `goHome()` - 즉시 **mainActivity**로 이동되며, **mainActivity**를 제외한 모든 액티비티가 종료됩니다.
   ![](images/activity_gohome.png)

3. `closeActivity("xxx")` - 특정 액티비티를 종료합니다.(**mainActivity** 제외) 해당 액티비티가 최상위 액티비티가 아니면, 하위 액티비티의 `onUI_show`는 호출되지 않습니다.