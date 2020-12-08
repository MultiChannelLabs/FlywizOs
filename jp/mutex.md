# Mutex/lock
 他の章で紹介したthreadはどのような場合に、プログラムにバグを引き起こす可能性があります。
 Multi-threadedプログラミングでこう現状況は非常に一般的です。
 簡単に理解するために、次のコードでこのような状況を説明します。  
 `struct Student`をグローバル変数として宣言した後、2つのthreadを定義します。A threadは`student`変数に値を代入して、B threadは` student`の値をコピーして、各メンバ変数の値をログに出力します。  
**Question : もし両方のthreadが同時に起動すると、B threadから出力される結果は、どうなるでしょう？**

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

まず、私たちが望む結果は以下の通りです。
```
name：David
age：10
student id number：20200101
```
しかし、実際の十分なテストを行う場合には、ほとんどの結果は、我々が予想していた結果を出力しますが、以下のような結果が出力される場合も発生します。
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

もしプログラムで "abnormal"した結果が出た場合は、これはバグで判断することができます。
## 原因分析  
 Multiple threadsプログラムでthreadの実行順序は、システムのスケジューリングによって決定されます。A threadのinstructionsをすべて実行した後、B threadのinstructionを実行し、再びA threadのinstructionsを実行することもできます。 
 上記の例では、`student`変数に完全な値を割り当てるための3つのstatementsがあります。もし最初のstatementのみが実行されたとき（`name`の値だけ割り当てられる）、システムがB threadでスイッチングをしました。 その後、この時B threadが読む`student`は`name`のみ有効であり、`age`と`number`は0である状態で「abnormal」が発生します。

## 解決方法  
 これらの理由から、A threadのinstructionsがすべて完了した後、B threadにスイッチングすることを確立することができている場合、この問題は解決されます。

## 実装方法
 これらのプログラムで**mutual exclusion lock**は、データ共有のための整合性を確立してくれることができる概念です。「mutual exclusion lock」と呼ばれることがあると、そのオブジェクトは、いくつかの瞬間でも一つのthreadのみ、そのオブジェクトにアクセスすることができます。
 以下はFlywizOSで提供される**mutual exclusion lock**機能です。

  1. Mutex 定義

```C++
static Mutex mutex1;
```
  2. Lockが必要なところ`Mutex:: Autolock` class instanceを定義します。  

```C++
// This class utilizes the life cycle of local variables and the structure and destructor of C++ classes to automatically 
// implement locking and unlocking operations.
Mutex::Autolock _l(mutex1);
```

 次のコードは、上記のAとB thread例を用いて修正されたコードです。
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
 コードでlockは、両方のthreadで`student`と関連して動作します。  
 A threadが実行されたとき、`Mutex:: Autolock_lock(mutext1);` statementを通じて`mutex1`の`mutex`が得られます。以後A threadがunlockされず、B threadが実行されると、B threadも`Mutex:: Autolock_lock(mutext1);` statementで`mutext1`の`mutex`を欲しくなります。 しかし、この`mutex`はすでにA threadによって獲得されたのでB threadがこれ獲得するためには、A threadがその`mutex`をunlockするのを待つしかなく、`mutex`を獲得した後に、通常次のstatementに進むことができます。

 基本的なプロジェクトにもこれと関連したコードを参照することができます。(`jni/uart/ProtocolParser.cpp`)
```c++
void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		sProtocolDataUpdateListenerList.push_back(pListener);
	}
}
```



Note : 以上の例でmutexの概念を十分に理解していなかった場合、インターネットを介して、より多くの情報を得ることができます。
Note : FlywizOSのシステムは、Linuxをベースにしており、standard Linuxのmutexも使用することができます。