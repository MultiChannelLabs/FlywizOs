# 터치 보정
 압력식 터치 스크린 보드는 처음 켜지면 터치 보정이 수행됩니다. 터치 보정 액티비티는 다음과 같습니다.

![](images/touchcalibration.png)

터치를 보정하려면 "십자 아이콘"을 클릭합니다. 추후 다시 보정하고 싶은 경우에는 다음의 세 가지 방법이 있습니다.
1. IDE를 통해 프로젝트 속성을 열고 **Touch calibration after booting** 옵션을 체크하여 전원을 켤 때마다 터치 보정 액티비티가 실행되도록 합니다.

   ![](images/touch_property.png)  <br/>
2. TF 카드의 루트 디렉토리에 **zktouchcalib** 파일을 생성합니다 (참고 : 파일에는 확장자가 없음). 카드를 삽입하면 터치 보정 액티비티로 들어갑니다.

   ![](images/zktouchcalib.png)  <br/>
3. 아래 코드로 터치 보정 액티비티를 시작합니다.
```c++
EASYUICONTEXT->openActivity("TouchCalibrationActivity");
```
