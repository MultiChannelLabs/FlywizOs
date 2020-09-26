
# <span id = "project_structure">FlywizOS 프로젝트의 코드 구조 소개</span>
 코드 작성을 시작하기 전에 먼저 FlywizOS 프로젝트의 기본 구조를 이해해야 코드를 추가해야하는 위치를 알 수 있습니다.
 기본 FlywizOS 프로젝트의 경우 디렉터리 구조는 다음과 같습니다.

![项目结构](assets/project_structure.png)  
대략 **jni**, **resources**, **ui**의 세 폴더로 나뉩니다. 각 폴더의 역할은 아래에 설명되어 있습니다.



* ## ui폴더  
  **ui**폴더 확장합니다. 
  
  ![ui폴더 확장](assets/project_ui_expand.png)    
  
   **main.ftu** 파일이 기본적으로 포함되어 있음을 알 수 있습니다. **ftu**는 **FlywizOS** 프로젝트 UI 파일의 접미사입니다. 각 **ftu** 파일은 액티비티에 해당합니다. 일반적으로 애플리케이션에는 여러 액티비티가 포함되어 있으므로 **ui** 폴더에 여러 **ftu** 파일을 만들어야합니다. 새 **ftu** 파일을 추가하려면 [새로운 FlyThings UI 파일 생성 방법](new_flywizOS_ui_file.md)을 참조하세요. 설명의 편의를 위해 이후부터는 **ftu** 파일을 **UI 파일**이라고 하겠습니다..
  
   더블 클릭하여 **UI 파일**을 열고 편집하여 즉시 효과를 미리 볼 수 있습니다. **UI** 파일 편집의 특정 단계는 **컨트롤 소개**를 참조하십시오.
  편집 후 **"compile"**을 시작할 수 있습니다. ([컴파일 방법](how_to_compile_flywizOS.md))
  
> [!Note]
  > **참고 : 여기에 언급 된 컴파일은 소스 코드의 컴파일일뿐만 아니라 ui 파일의 전처리 및 템플릿 코드 생성과 같은 일련의 작업이기도 하지만 이러한 작업은 모두 자동화되어 있으므로 수동으로 작업 할 필요가 없습니다. 컴파일 - 이 작업의 모든 특정 작업에 대해서는 [컴파일 과정 및 UI 파일과 소스 코드 간의 상관 관계](ftu_and_source_relationships.md # ftu_and_source_relationships)를 참조하십시오. 이를 읽은 후에는 이해하기 쉽고 빠르게 시작할 수있을 것입니다** 

* ## resources folder  
   이 폴더의 내용은 비교적 간단하며 주로 그림, 폰트, 입력 방법 구성 파일 등을 포함하여 프로젝트의 다양한 리소스 파일을 저장하는 데 사용됩니다. 다른 리소스 파일이있는 경우 이 폴더에 추가 할 수도 있습니다. 폴더는 시스템에 완전히 복사됩니다. 단, 기기 자체 저장 공간의 제한으로 이 디렉토리에 대용량 파일을 저장하지 않는 것이 좋으며 대용량 리소스 파일은 TF 카드에 저장하는 것이 좋습니다.
  
   코드의 resources 디렉토리에있는 파일의 절대 경로를 얻을 수 있습니다.  
   예 : 다음 코드는 resources / test.txt의 절대 경로를 가져올 수 있습니다.
   ```c++ 
  #include "manager/ConfigManager.h"
  std::string resPath = CONFIGMANAGER->getResFilePathEx("test.txt");
   ```
* ## jni folder  
   이 폴더는 주로 코드 파일을 저장하는 데 사용됩니다. **jni** 폴더를 확장합니다.  
   ![](assets/project_jni_expand.png)  
   위에 보이는 것처럼 여기에는 **activity**, **include**, **logic**, **uart**, **Main.cpp**, **Makefile**의 6 개 부분이 포함되어 있습니다. 각 부분의 기능은 다음과 같습니다.
   
   * ### activity subfolder  
     UI 파일의 기본 클래스 코드를 저장합니다. 각 UI 파일이 컴파일 된 후 동일한 접두사 이름을 가진`Activity` 클래스와`Logic.cc` 파일이 생성됩니다. 
     예 : ui 폴더에 **main.ftu**가 있는 경우 컴파일 후 `mainActivity.h`, `mainActivity.cpp` 및 `mainLogic.cc`가 생성되고 `mainActivity` 클래스가 **activity**폴더에 저장됩니다. `mainLogic.cc` 파일은 **logic** 폴더에 저장됩니다.
     
     > [!Warning] 
     > **특별한 상황을 제외하고 activity 폴더 아래의 코드는 수정하지 않는 것이 좋습니다.**
          
   * ### logic subfolder   
      특정 논리 코드를 저장합니다. 위의 설명과 동일하게 모든 UI 파일은 컴파일 후 해당 접두사 이름이 있는 **Logic.cc** 파일을 생성합니다. **참고 : 사용자 지정 코드는 주로 이러한 Logic.cc 파일에 추가됩니다**.
          
   * ### include subfolder   
     시스템 관련 헤더 파일 및 모든 컨트롤 관련 헤더 파일이 주로 여기에 저장됩니다.
      
   * ### uart subfolder     
      이름에서 알 수 있듯이 이 폴더에는 시리얼 포트 읽기 및 쓰기, 프로토콜 분석 등을 포함한 시리얼 포트 작동 관련 코드가 저장됩니다.
          
   * ### Main.cpp   
      부팅 및 시작 액티비티를 선택하는 함수등 전체 FlywizOS 응용 프로그램의 초기화 코드를 포함하며 일반적으로 파일을 수정할 필요가 없습니다.
      
   * ### Makefile/Android.mk、Application.mk   
      특정 소스 코드 컴파일 프로세스를 포함하는 컴파일 구성 파일로 일반적으로 수정할 필요가 없습니다. 

 컴파일 후 **libs** 디렉토리와 **obj** 디렉토리가 프로젝트 아래에 생성됩니다. 이 디렉토리는 컴파일된 대상 저장소 디렉토리와 컴파일된 임시 파일 디렉토리이며 둘 다 직접 정리하거나 삭제할 수 있습니다.

