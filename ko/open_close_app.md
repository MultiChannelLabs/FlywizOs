 앞서 우리는 이미 시작 액티비티에 대해 배웠습니다. 시작 액티비티 실행 후 두 번째, 세 번째 단계의 다른 액티비티를 실행할 수 있습니다. 다음으로 다른 액티비티를 실행하고 종료하는 방법에 대하여 배우도록 하겠습니다.

## Application activity 실행
 예를 들어 이제 **sub.ftu**.에 해당하는 액티비티를 실행해야 합니다. 앞서 시작 액티비티의 분석에 따라 UI 리소스에 해당하는 액티비티 객체가 **subActivity**임을 알 수 있습니다. 이것들은 IDE에 의해 자동으로 코드들입니다. 우리는 여기에서 너무 많은 세부 사항에 주의를 기울일 필요가 없이 간단히 이애해는 것으로 다음 코드로 액티비티를 시작할 수 있습니다. 

```c++
EASYUICONTEXT->openActivity("subActivity");
```
 만약 버튼 클릭을 통해 **sub.ftu** 액티비티로 진입하려면 버튼 클릭 이벤트 함수에서 위의 statement를 호출할 수 있습니다.
```c++
static bool onButtonClick_Button1(ZKButton *pButton) {
    // Jump to the sub.ftu activity 
    EASYUICONTEXT->openActivity("subActivity");
    return false;
}
```
 정상적인 상황에서는, 위의 호출 코드로 충분합니다. 그러나 결제 페이지처럼 액티비티 간에 어떤 정보를 전달할 필요가 있다면, openActivity로 전달되는 두 번째 파라미터를 사용해서 정보를 전달해야합니다.
```c++
Intent *pIntent = new Intent();
pIntent->putExtra("cmd", "open");
pIntent->putExtra("value", "ok");
EASYUICONTEXT->openActivity("subActivity", pIntent);
```
 **subLogic.cc**의`onUI_intent` 콜백에서 수신 할 수 있습니다.
```c++
static void onUI_intent(const Intent *intentPtr) {
	if (intentPtr) {
		// Key value analysis
		std::string cmd = intentPtr->getExtra("cmd");		// "open"
		std::string value = intentPtr->getExtra("value");	// "ok"
		......
	}
}
```
Note：

	1. 새로운 인텐트는 수동으로 삭제할 필요가 없으며 프레임 워크 내에서 자동으로 삭제됩니다.
	2. putExtra는 string의 key-value pair 메소드 만 제공합니다. int 또는 다른 유형의 값을 전달해야하는 경우 문자열 유형으로 변환 한 다음 onIntent에서 수신 한 후 해당 변환을 수행해야합니다.

## Application activity 종료</span>
 위의 openActivity함수를 통해 subActivity를실행했는데, 원래 액티비티로 돌아가고 싶으면 어떻게 해야할까요?
 다음 코드를 통해 이전 액티비티로 돌아갈 수 있습니다.

```c++
EASYUICONTEXT->goBack();
```
 버튼에 의해 goBack()이 트리거되는 경우, IDE를 사용하여 버튼의 ID 값을 `sys_back`으로 하는 것으로 직접 goBack() 기능을 사용할 수 있습니다.

![](images/Screenshotfrom2018-06-06220522.png)


 만약 보다 계층적인 액티비티에서 바로 시작 액티비티로 돌아가길 원한다면, 아래 코드로 구현 가능합니다.

```c++
EASYUICONTEXT->goHome();
```
 시작 액티비티로 돌아갑니다.
 또한 버튼으로 트리거되는 경우 IDE를 사용하여 버튼의 ID값을 `sys_home`으로 하는 것으로 직접 goHome()기능을 사용할 수 있습니다.
 끝으로, EasyUIContext의 closeActivity함수를 통해 액티비티를 종료할 수도 있습니다. 예를 들어 subActivity를 종료하고 싶습니다.

```c++
EASYUICONTEXT->closeActivity("subActivity");
```
 이 함수를 사용하려면 호출자가 종료할 액티비티의 이름을 알아야합니다. 
 Note : 이 함수는 시작 액티비티를 종료할 수 없습니다. 시작 액티비티는 항상 존재합니다.