# c++ 기본 지식
이 장에서는 C++에 대한 기본 지식이 없는 사람들에게 C++의 기본 문법과 클래스에 대해 설명합니다.

## Class
C++의 경우 먼저 **class**를 언급해야합니다. 너무 복잡하다고 생각하지 말고 C 언어의 structure로 이해하도록 합니다.  
예를 들어  :
* 구조체 정의
```c++
// C
struct Position {
	int left;
	int top;
	int width;
	int height;
};

// c++
class Position {
public:
	int left;
	int top;
	int width;
	int height;
};
```

* 변수 정의 :
```c++
// C
struct Position pos;

// c++
Position pos;
```

* 변수 운영 :
```c++
// C is the same as c++
pos.left = 0;
```
 
**class**에는 C 언어의 구조보다 상속, 다형성, 오버로딩 및 액세스 권한에 대한 개념이 더 많습니다. C에 익숙한 사람들은 이것을 어떻게 사용해야 하는지 충분히 알기 위해서가 아니라면, 많은 노력을 기울일 필요가 없습니다.  
추가적으로 C언어에서는 함수 포인터만 정의하지만 C++의 **class**에서는 함수를 바로 구현 가능합니다. 이 부분이 C와는 다른 점으로, **class**에 정의된 함수는 일종의 변수처럼 사용됩니다. 아래는 자주 사용되는 예제입니다.

```c++
// Set the text content, where mTextView1Ptr is a pointer variable of type ZKTextView
mTextView1Ptr->setText("Hello");
```

## 기본 class
### string class
string class는 실제 string과 이를 위해 제공되는 많은 함수들이 캡슐화 되어있습니다. 그러나 C에 익숙한 사용자는 `c_str()`함수만 알아도 충분히 활용 가능합니다. 이 함수는 string class에서 characters만 반환하는 함수로 아래와 같이 사용할 수 있습니다.
```c++
// Input box callback function
static void onEditTextChanged_Edittext1(const std::string &text) {
	// The return value type of c_str() function : const char *
	const char *pStr = text.c_str();
	
	// Then you can operate like ordinary strings, such as getting the string length strlen(pStr), etc.
}
```
아래는 텍스트 컨트롤에서 텍스트를 가져오는 예제입니다.
```c++
// std is the namespace, std::string means to use the string class under std, don’t worry too much 
// When encountering the string class, we can refer to the following definition
std::string text = mTextView1Ptr->getText();

// The subsequent operations are the same
const char *pStr = text.c_str();
```

## <span id="snprintf">snprintf</span>
### 함수 프로토타입 :
  ```c++
  int snprintf(char* dest_str,size_t size,const char* format,...);
  ```
### 기능 : 
  여러 파라미터를 정해진 포맷에 맞게 string화 하여 dest_str에 저장
  (1) 만약 formatted string의 length가 size보다 작은 경우 string이 복사되고 string의 끝에 '\0'이 추가됩니다.  
  (2) 만약 formatted string의 length가 size보다 크거나 같은 경우 오직 size-1의 string만 카피되고 마지막에 '\0'이 추가됩니다.

### 필요 헤더 파일 :
  ```c++
  #include <stdio.h>
  ```

### 포맷 형식
* Specifier  
  `%d` Decimal signed integer  
  `%u` Decimal unsigned integer  
  `%f` Floating point  
  `%s` String  
  `%c` Character  
  `%p` Pointer value  
  `%e` Exponential floating point  
  `%x`, %X Unsigned integer in hexadecimal  
  `%o` Unsigned integer in octal  
  `%g` Output the value according to the smaller output length in %e or %f type  
  `%p` Output address  
  `%lu` Output long integer
  `%llu` 64-bit unsigned integer   
* Description  
    (1) 최대 필드 너비를 나타 내기 위해 "%"와 문자 사이에 숫자를 삽입 할 수 있습니다.
    예 : %3d는 3개의 정수 출력을 의미합니다. 3자리가 안된다면 오른쪽으로 정렬됩니다. 
    %9.2f는 필드 너비가 9인 부동 소수점 숫자를 나타냅니다. 여기서 소수점 자리는 2이고 정수 자리는 6입니다. 소수점이 한 자리이며 9자리가 안된다면 오른쪽으로 정렬됩니다.
    %8s는 8자 문자열을 출력하는 것을 의미하며, 8자가 안된다면 오른쪽 정렬됩니다.
    문자열의 길이나 정수의 개수가 지정된 필드 너비를 초과하면 실제 길이에 따라 출력됩니다.
    그러나 부동 소수점 숫자의 경우 정수 개수가 지정된 정수 너비를 초과하면 실제 정수로 출력됩니다. 
    소수점 이하 자릿수가 지정된 소수점 이하 자릿수를 초과하면 지정된 너비에 따라 출력이 반올림됩니다. 
    또한 출력 값 앞에 0을 추가하려면 필드 너비 용어 앞에 0을 추가해야합니다. 
    예 : %04d는 4 자리 미만의 값을 출력 할 때 앞에 0이 추가되어 총 너비가 4 자리가됨을 의미합니다. 
    부동 소수점 숫자를 사용하여 문자 또는 정수의 출력 형식을 나타내는 경우 소수점 뒤의 숫자는 최대 너비를 나타내고 소수점 앞의 숫자는 최소 너비를 나타냅니다. 
    예 : %6.9s는 길이가 6 이상 9 이하인 문자열을 표시 함을 의미합니다. 9보다 크면 9 번째 문자 이후의 내용은 삭제됩니다. 
    (2) "%"와 문자 사이에 소문자 l을 추가하여 출력이 긴 숫자임을 나타낼 수 있습니다. 
    예 : %ld는 long 출력을 의미합니다. 
    %lf는 출력 double-float 숫자를 의미합니다. 
    (3) 출력을 왼쪽 정렬 또는 오른쪽 정렬로 제어 할 수 있습니다. 즉, "%"와 문자 사이에 "-"기호를 추가하여 출력이 왼쪽 정렬됨을 나타내며 그렇지 않으면 오른쪽 정렬됩니다.
    예 : %-7d는 출력 7개 정수가 왼쪽 정렬됨을 의미합니다.
    % -10s는 왼쪽 정렬 된 10 자 출력을 의미합니다.  
* Special specifier  
  `\n` 줄 바꿈  
  `\f` 화면 지우기 및 페이지 변경  
  `\r` 캐리지 리턴  
  `\t` Tab

### 예제
  * 정수 출력
  ```c++
  char buf[64] = {0};
  snprintf(buf, sizeof(buf), "%d", 314);
  LOGD("%s", buf);//Log output buf
  ```
  출력된 log :
  ```
  314
  ```

  * 정수의 자릿수 지정 출력
  ```c++
  char buf[64] = {0};
  snprintf(buf, sizeof(buf), "%05d", 314); //Format as 5 digits, less than 5 digits, add 0 in front
  LOGD("%s", buf);//Log output buf string
  ```
  출력된 log :  
  ```
  00314
  ```
  * 부동 소수점 출력
  ```c++
  char buf[64] = {0};
  snprintf(buf, sizeof(buf), "%f", 3.14); 
  LOGD("%s", buf);//Log output buf string
  ```
  출력된 log :  
  ```
  3.140000
  ```

  * 부동 소수점 자리수 지정 출력
  ```c++
  char buf[64] = {0};
  //Output decimals, a total of 6 characters wide (including the decimal point), 3 decimal places, two integer digits, and 0 if   //the integer is less than two digits
  snprintf(buf, sizeof(buf), "%06.3f", 3.14);
  LOGD("%s", buf);//Log output buf string
  ```
  출력된 log :  
  ```
  03.140
  ```
