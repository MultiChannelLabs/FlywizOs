#  원형 프로그래스 바
특정 어플리케이션의 경우 "일직선의 프로그래스 바" 보다 "원형의 프로그래스 바"가 더 적합할 수 있습니다. 

## 사용법 
1. 먼저 UI파일을 오픈 후 **circular progress bar** 컨트롤을 만듭니다. 그리고 **valid picture** 속성에 이미지를 추가하면 기본적인 원형 프로그래스 바가 완성됩니다.  
   원형 프로그래스 바의 모든 속성은 아래와 같습니다.  
   ![](assets/circlebar/property.png)

2. 원형 프로그래스 바는 현재의 프로그래스가 부채꼴 영역으로 표시되며, 이 영역은 **valid picture**의 일정 영역만을 디스플레이 하는 것으로 구현됩니다. 예를 들어, 만약 속성이 위의 이미지와 같이 설정되었다면, 최대 값은 100이고, 초기 시작 각도는 0°이며 프로그래스의 방향은 시계방향입니다. 그 후 프로그래스를 25로 설정한다면 오직 0°부터 90°의 부채꼴 영역에 해당하는 valid picture만 표시됩니다. 그리고 만약 프로그래스가 100이라면 전체 valid picture가 표시됩니다.
   
> Note: 프로그래스 값에 따른 디스플레이 영역의 변경은 **valid picture**에만 적용되고, **background picture**에는 적용되지 않습니다.  
   ![](assets/circlebar/location.png)

## 운용 코드
원형 프로그래스 바에서 제공하는 함수는 매우 단순합니다.
```c++
//Set current progress
void setProgress(int progress);
//Get current progress
int getProgress()；

//Set maximum progress
void setMax(int max);
//Get maximum progress
int getMax()；
```

# 예제 코드
예제에서 위쪽 슬라이드 바를 조정하면 아래의 2개 원형 프로그래스 바가 변경됩니다.  
[Sample code](demo_download.md#demo_download)의 CircleBarDemo 프로젝트 참고하십시오.
![](assets/circlebar/preview.png)  
