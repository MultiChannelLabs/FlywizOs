# Mutex/lock
다른 챕터에서 소개했던 thread는 어떤 경우에 프로그램에 버그를 일으킬 수 있습니다.  
Multi-threaded 프로그래밍에서 이러현 상황은 매우 일반적입니다.  
쉬운 이해를 위해 아래의 코드로 이 상황을 설명하겠습니다.  
`struct Student`를 전역 변수로 선언 후 2개의 thread를 정의합니다. A thread는 `student`변수에 값을 할당하고, B thread는 `student`의 값을 복사하여 각 멤버변수의 값을 로그로 출력합니다.
**Question : 만약 두 thread가 동시에 시작되면 B thread에서 출력되는 결과는 어떻게 될까요?**

```c++
#include <system/Thread.h>

struct Student {
  char name[24];
  int age;
  int number;
};

struct Student student = {0};

class AThread: public Thread {
public:
  virtual bool threadLoop() {
    snprintf(student.name, sizeof(student.name), "David");
    student.age = 10;
    student.number = 20200101;
    return true;
  }
};

class BThread: public Thread {
public:
  virtual bool threadLoop() {
    struct Student s = student;
    LOGD("name : %s", s.name);
    LOGD("age : %d", s.age);
    LOGD("student id number : %d", s.number);
    return true;
  }
};

static AThread athread;
static BThread bthread;
```

먼저 우리가 원하는 결과는 아래와 같습니다.
```
name：David
age：10
student id number：20200101
```
그러나 실제로 많은 테스트를 할 경우, 대부분의 결과는 우리가 예상했던 결과를 출력하지만 아래와 같은 결과가 출력되는 경우도 발생합니다.
```
name：
age：0
student id number：0
```
```
name：xiaoming
age：0
student id number：0
```
```
name：xiaoming
age：10
student id number：0
```
만약 프로그램에서 "abnormal"한 결과가 나온다면, 이것은 버그로 판단할 수 있습니다.

## 원인 분석  
Multiple threads 프로그램에서 thread의 실행 순서는 시스템의 스케쥴링에 의해 결졍됩니다. A thread의 instructions를 모두 실행한 후 B thread의 instruction을 실행하고, 다시 A thread의 instructions를 실행할 수도 있습니다. 
위의 예제에서 `student`변수에 완전한 값을 할당하기 위한 3개의 statements가 있습니다. 만약 첫 statement만 실행되었을 때(`name`의 값만 할당됨), 시스템이 B thread로 스위칭을 했습니다. 그러면 이때 B thread가 읽는 `student`에는 `name`만 유효하고, `age`와 `number`는 0인 상태로 'abnormal'이 발생합니다.

## 해결 방법  
이러한 이유로 A thread의 instructions들이 모두 완료가 된 후 B thread로 스위칭한다는 것을 확립할 수 있다면 이 문제는 해결됩니다.

## 구현 방법
이러한 프로그램에서 **mutual exclusion lock**은 데이터 공유에 대한 무결성을 확립해줄 수 있는 개념입니다. "mutual exclusion lock"이라 불릴 수 있는 해당 객체는 어떤 순간에서든 하나의 thread에서만 해당 객체에 접근할 수 있습니다.  
아래는 FlywizOS에서 제공하는 **mutual exclusion lock** 기능입니다.

1. Mutex 정의
   ```C++
   static Mutex mutex1;
   ```

2. Lock이 필요한 곳에 `Mutex::Autolock` class instance를 정의합니다.
   ```C++
   // This class utilizes the life cycle of local variables and the structure and destructor of C++ classes to automatically 
   // implement locking and unlocking operations.
   Mutex::Autolock _l(mutex1);
   ```
아래 코드는 위의 A와 B thread 예제를 이용해 수정된 코드입니다.
```c++
#include <system/Thread.h>

struct Student {
  char name[24];
  int age;
  int number;
};

struct Student student = {0};
//Define a mutex 
static Mutex mutext1;

class AThread: public Thread {
public:
  virtual bool threadLoop() {
    //Lock the statement of the function, and automatically unlock after the function ends
    Mutex::Autolock _lock(mutext1);
    snprintf(student.name, sizeof(student.name), "David");
    student.age = 10;
    student.number = 20200101;
    return true;
  }
};

class BThread: public Thread {
public:
  virtual bool threadLoop() {
    //Lock the statement of the function, and automatically unlock after the function ends
    Mutex::Autolock _lock(mutext1);
    struct Student s = student;
    LOGD("nanme：%s", s.name);
    LOGD("age：%d", s.age);
    LOGD("student id number：%d", s.number);
    return true;
  }
};

static AThread athread;
static BThread bthread;
```

코드에서 lock은 두 thread에서 `student`와 관련하여 동작합니다.  
A thread가 실행되었을 때, `Mutex::Autolock _lock(mutext1);` statement를 통해 `mutex1`의 `mutex`가 얻어집니다. 이후 A thread가 unlock되지 않고 B thread가 실행되면 B thread 역시  `Mutex::Autolock _lock(mutext1);` statement로 `mutext1` 의 `mutex`을 원하게 됩니다. 그러나 이 `mutex`는 이미 A thread에 의해 획득되었기에 B thread가 이를 획득하기 위해서는 A thread가 해당 `mutex`를 unlock하는 것을 기다릴 수 밖에 없고, `mutex`를 획득 한 후에야 정상적으로 다음 statement로 진행할 수 있습니다.

기본적인 프로젝트에도 이와 관련한 코드를 찾아볼 수 있습니다.(`jni/uart/ProtocolParser.cpp`)
```c++
void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		sProtocolDataUpdateListenerList.push_back(pListener);
	}
}
```
> Note : 이상의 예제로 mutex에 대한 개념을 충분히 이해하지 못했다면 인터넷을 통해 더 많은 정보를 얻을 수 있습니다.  
> Note : FlywizOS의 시스템은 Linux를 기반으로 하고 있어 standard Linux의 mutex도 사용할 수 있습니다.