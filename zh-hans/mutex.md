# 互斥量/锁
当我们的程序里引入线程后，某些情况下又会引出其他问题，导致程序Bug。  

多线程编程中，这样的情况非常普遍：就是A线程对一个变量赋值，然后B线程读这个值。  
为了方便说明，我们将这种情况翻译为下面的代码。  
定义一个`struct Student`全局变量，还定义两个线程，A线程负责对`student`变量赋值；  
B线程对`student`变量做了拷贝，并读出变量的各个成员，显示到日志上。  
**请问：如果同时启动两个线程，那么B线程的日志会输出怎样的结果？**
```c++
#include <system/Thread.h>

struct Student {
  char name[24]; //姓名
  int age;       //年龄
  int number;    //学号
};

struct Student student = {0};

class AThread: public Thread {
public:
  virtual bool threadLoop() {
    snprintf(student.name, sizeof(student.name), "xiaoming");
    student.age = 10;
    student.number = 20200101;
    return true;
  }
};

class BThread: public Thread {
public:
  virtual bool threadLoop() {
    struct Student s = student;
    LOGD("姓名：%s", s.name);
    LOGD("年龄：%d", s.age);
    LOGD("学号：%d", s.number);
    return true;
  }
};

static AThread athread;
static BThread bthread;
```

首先，我们希望的结果是日志里输出  
```
姓名：xiaoming
年龄：10
学号：20200101
```
实际上，如果测试的次数足够多，可能大部分的输出与我们期望的相同，还有可能会输出以下这些结果：  
```
姓名：
年龄：0
学号：0
```
```
姓名：xiaoming
年龄：0
学号：0
```
```
姓名：xiaoming
年龄：10
学号：0
```

如果程序中出现了 “异常” 结果，肯定算是一个Bug了。  
## 分析原因    
  当程序存在多线程时，线程执行顺序是由系统灵活调度的，可能出现A线程执行了一部分指令，又转到B线程执行一部分指令，又转到A线程执行指令。  
  对上面的例子而言， A线程中，共有三条语句完成对 `student` 变量的完整赋值，当只执行完第一条语句，仅完成了对 `name` 的赋值，此时系统转而切换到B线程，  
  那么B线程中，这时读取 `student` 变量，就会出现 `name` 字段有效，而 `age` 和 `number`为0的情况。
  其他的异常结果，同理。 

## 如何解决   
  由原因得出，只要我们保证A线程中， `student` 的所有赋值操作都完成后，B线程再去读 `student`变量，这样就没有问题了。  

## 如何实现  
  在编程中，有一个 **互斥锁** 的概念，来保证共享数据操作的完整性。每个对象都对应于一个可称为" 互斥锁" 的标记，这个标记用来保证在任一时刻，只能有一个线程访问该对象。  
  如果你熟悉Linux编程，可以用标准实现。这里我们介绍我们封装的 互斥量类 使用。  
  
  1. 定义一个互斥量  
    ```c++
    static Mutex mutex1;
    ```
  2. 在需要加锁的地方，定义局部 `Mutex::Autolock` 类实例加锁。  
    该类利用了局部变量的生命周期以及c++的类的构造、析构函数，自动实现加锁、解锁操作。
    ```c++
    Mutex::Autolock _l(mutex1);
    ```    
    
结合上面A、B线程的例子，修改的代码如下：  
```c++
#include <system/Thread.h>

struct Student {
  char name[24]; //姓名
  int age;       //年龄
  int number;    //学号
};

struct Student student = {0};
//定义互斥量
static Mutex mutext1;

class AThread: public Thread {
public:
  virtual bool threadLoop() {
    //在该函数的语句进行加锁，函数结束后，自动解锁
    Mutex::Autolock _lock(mutext1);
    snprintf(student.name, sizeof(student.name), "xiaoming");
    student.age = 10;
    student.number = 20200101;
    return true;
  }
};

class BThread: public Thread {
public:
  virtual bool threadLoop() {
    //在该函数的语句进行加锁，函数结束后，自动解锁
    Mutex::Autolock _lock(mutext1);
    struct Student s = student;
    LOGD("姓名：%s", s.name);
    LOGD("年龄：%d", s.age);
    LOGD("学号：%d", s.number);
    return true;
  }
};

static AThread athread;
static BThread bthread;
```
代码中，我们对A、B线程内，`student`相关的操作都进行了加锁。    
当执行A线程时，`Mutex::Autolock _lock(mutext1);` 语句会获得 `mutex1`互斥量，当A线程没有解锁，又转去执行B线程时，  
执行到B线程内的 `Mutex::Autolock _lock(mutext1);` 语句，它也想获得 `mutext1`互斥量，但是，这个互斥量已经被A线程抢先获得，现在B线程想要获得的话，只能等，等到A线程释放 `mutext1` ，B线程才能正常获得 `mutext1` 互斥量，然后继续执行接下来的语句。  
使用互斥量后，使得被加锁的代码部分，能够互斥执行，且保证完整性。    

在我们的项目中，也有一个用到互斥量的例子，见源码 `jni/uart/ProtocolParser.cpp` ：
```c++
void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		sProtocolDataUpdateListenerList.push_back(pListener);
	}
}
```

如果对互斥量概念还不够理解，可以从网上获取更多关于 **互斥量**的资料。
  