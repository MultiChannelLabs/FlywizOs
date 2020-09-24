# RadioGroup
 여러 옵션, 단일 선택의 경우 `RadioGroup` 컨트롤을 직접 사용할 수 있습니다.
 옵션 중 하나를 클릭하면 옵션이 자동으로 선택된 상태로 전환되고 동일한 그룹의 다른 옵션은 선택되지 않은 상태가됩니다. 이러한 옵션의 상태를 전환하는 동안 그림과 색상도 속성 창의 설정에 따라 자동으로 전환됩니다.

## How to use
1. 더블 클릭하여 UI 파일을 엽니다.
2. 우측의 컨트롤 박스에서  `RadioGroup` 컨트롤을 찾습니다.
   ![](assets/radiogroup/r1.png)  
   ![](assets/radiogroup/option.png) 
3. `RadioGroup`컨트롤에서 마우스 왼쪽 버튼을 클릭 한 상태에서 원하는 위치로 드래그 한 후 왼쪽 버튼을 놓으면 자동으로 직사각형 영역이 생성되는 것을 볼 수 있고, 그 역역은 `RadioButton`컨트롤을 보유 할 수있는 컨테이너를 나타냅니다.
4. 동일한 드래그 앤 드롭 작업을 사용하여 지금 바로 직사각형 영역에 여러 `RadioButton` 컨트롤을 추가 할 수 있습니다.
5. 추가 된 `RadioButton` 컨트롤을 마우스 왼쪽 버튼으로 클릭하면 우측에서 관련 속성을 볼 수 있습니다.
   필요에 따라 각 컨트롤의 각 상태 그림과 색상을 설정할 수 있습니다. 여기서 선택시 **Picture and Background Colors** 속성에 주의하십시오.

  ![](assets/radiogroup/properties.png)  

   그림을 설정 한 후 그림의 크기가 비정상적으로 표시되는 경우 **Picture Location** 속성에서 그림의 위치와 크기를 조정할 수 있습니다.
   **Default State** 속성에서 **Checked** 또는 **Unchecked**을 설정할 수도 있습니다.

6. 속성을 설정 한 후 컴파일하면 해당하는`Logic.cc`에 관련 함수가 생성됩니다.
   RadioButton 중 하나를 클릭하면 시스템에서 관련 함수를 호출합니다. 여기서 `int checkedID` 매개 변수는 선택한 RadioButton의 'ID'를 나타냅니다.
   이 ID 값을 기반으로 현재 클릭 된 RadioButton을 확인할 수 있습니다.
   이 'ID'는 매크로 정의 정수 값입니다. UI 파일이 컴파일 된 후 각 컨트롤은 해당 매크로 ID를 자동으로 생성합니다 (매크로에 대한 자세한 내용은 [이름 지정 규칙](name_rule.md # id_macro_rule)을 확인하십시오).
   각 옵션의 매크로 ID는 해당`Activity.h` 헤더 파일에서 찾을 수 있습니다. 예 :
   
   ![](assets/radiogroup/id.png)  
   
   그런 다음 상관 함수에서 클릭 항목을 판단 할 수 있습니다.
   ```c++
    static void onCheckedChanged_RadioGroup1(ZKRadioGroup* pRadioGroup, int checkedID) {
      LOGD("Checked ID = %d", checkedID);
      switch (checkedID) {
        case ID_MAIN_RadioButton1:
          LOGD("First RadioButton");
          break;
        case ID_MAIN_RadioButton2:
          LOGD("Second RadioButton");
          break;
        case ID_MAIN_RadioButton3:
          LOGD("Third RadioButton");
          break;
        default:
          break;
      }
    }
   ```

7. 다운로드 및 디버그, 효과를 확인합니다.


## Sample code  

[Sample Code](demo_download.md#demo_download)의 RadioGroupDemo 프로젝트를 참고하십시오.
예제 미리보기 :

![效果图](assets/radiogroup/example.png)
