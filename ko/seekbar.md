# Seek Bar 컨트롤
## Seek Bar 컨트롤 사용법
많은 어플리케이션에서 Seek Bar을 사용합니다. 예를 들면 다음과 같습니다.  
**Volume 조정**  
![](assets/seekbar/example-volume.png)  

몇 가지 간단한 그림을 사용하여 이 효과를 빠르게 얻을 수 있습니다.
1. 먼저 4개의 리소스 이미지를 준비합니다.
  * Background picture    
    ![](assets/seekbar/bg.png)  
  * Valid picture  
    ![](assets/seekbar/valid.png)
  * Thumb - normal picture   
    ![](assets/seekbar/c.png)
  * Thumb - pressed picture  
    ![](assets/seekbar/c_pressed.png)

2. 편집기에서 Seek Bar 컨트롤을 만듭니다.

   ![](assets/SeekBar-create.gif)

   컨트롤을 만드는 방법을 모르는 경우 [Button 컨트롤 만들기 참조](#add_button) 하십시오.

3. 기본 Seek Bar 스타일은 투명하며 정상적으로 동작하려면 이미지 리소스를 추가해야 합니다.
   속성 창에서 **Valid Picture, Thumb-Normal Picture, Thumb-Pressed Picture, Background Picture** 이미지를 설정합니다.

   ![](assets/seekbar/add-photo.gif)

4. 위 단계가 완료되면 기본적으로 Seek Bar생성이 완료됩니다. IDE에서 Seek Bar의 슬라이딩 효과를 미리 보려면 **Max Value**속성 및 **Default Progress**속성을 수정하십시오. 미리보기에서 슬라이더 커서의 위치 변경을 확인할 수 있습니다.
    
## 코드에서 Seek Bar의 프로그래스를 제어하는 방법은 무엇입니까? Seek Bar의 현재 프로그래스 값을 확인하는 방법은 무엇입니까?
Seek Bar를 사용하여 Volume Bar를 구현하는 경우 현재 Volume Bar의 프로그래스 값을 알아야하며 Volume Bar가 변경되면 동시에 볼륨도 조정해야 합니다. 따라서 이러한 문제를 해결하기 위해 다음과 같은 3가지 함수가 있습니다.

1. `static void onProgressChanged_XXXX(ZKSeekBar *pSeekBar, int progress)`  
   프로그래스 값 변경 모니터링 함수  
   UI 파일에 Seek Bar컨트롤을 생성한 후 컴파일 하면 이 함수가 해당 `XXXXLogic.cc`파일에 자동으로 추가됩니다. 터치 스크린에서 Seek Bar를 조작하거나 프로그래스의 현재 값이 변경되면 시스템이 이 함수를 자동으로 호출합니다.
   ```c++
   static void onProgressChanged_XXXX(ZKSeekBar *pSeekBar, int progress) {
      //LOGD("XXXXThe progress value of the seek bar changes to %d !\n", progress);
   }
   ```
2. `void setProgress(int progress)`  
   Seek Bar의 현재 프로그래스 값을 설정하는 데 사용됩니다.   
   예 :
   ```c++
   //Set the seek bar progress to 28
   mSeekbarPtr->setProgress(28)
   ```
3. `int getProgress()`  
   현재 Seek Bar의 프로그래스 값을 가져 오는 데 사용됩니다.   
   예 :
   ```c++
   int progress = mSeekbarPtr->getProgress();
   LOGD("The current progress value of the seek bar %s", progress);
   ```


## 예제 
더 자세한 내용은 [Sample Code](demo_download.md#demo_download)의 SeekBarDemo 프로젝트를 참고하십시오.

예제 미리보기 :

![](assets/seekbar/preview.png)
