# Thread
시스템은 `pthread`를 지원합니다. `pthread` 인터페이스를 이해하면 `posix` 인터페이스를 사용하여 thread를 구현할 수도 있습니다.
또한 `pthread`에 대한 래퍼 클래스도 제공합니다. 여기에는 다음 세 부분이 포함됩니다.

* Thread.h：Thread class
* Mutex.h：Mutex class
* Condition.h：Condition class

## 사용법
1. 헤더 파일을 인클루드한 후 `Thread`클래스를 상속하고 `virtual bool threadLoop()`함수를 구현합니다. 또한 필요에 따라 readyToRun()함수를 구현합니다.
   ```c++
   #include <system/Thread.h>
    
   class MyThread: public Thread {
   public:
      /**
       * After the thread is created successfully, this function will be called, and some initialization operations can be done 
       * in this function
       * return true   Continue thread
       *        false  Exit thread
       */
      virtual bool readyToRun() {
        LOGD("Thread has been created");
        return true;
      }

      /**
       * Thread loop function
       *
       * return true  Continue thread loop
       *        false Exit thread
       */
      virtual bool threadLoop() {
        LOGD("Thread loop function");

        //Check if there is a request to exit the thread, if so, return false and exit the thread immediately
        if (exitPending()) {
          return false;
        }

        //Accumulate the count and display it on the screen
        loop_count += 1;
        mTextView2Ptr->setText(loop_count);

        //To observation, add sleep 500ms here
        usleep(1000 * 500);

        //Return true, continue the next thread loop
        return true;
      }
   };
   ```

2. Thread object 인스턴스화
  ```c++
  static MyThread my_thread;
  ```

3. Thread 시작
   ```c++
   //Call the run function of the thread class to start the thread
   //The parameter is the thread name, which can be arbitrarily specified.
   my_thread.run("this is thread name");
   ```
4. Thread 종료
   `Thread`클래스는 thread의 종료를 요청하는 동기식과 비동기식의 두 가지 함수를 제공하며 차이점은 다음과 같습니다.
   * **void requestExitAndWait()**  
     ```c++
     //Request to exit the thread and wait. The function does not return until the thread completely exits
     my_thread.requestExitAndWait();
     ```
   * **void requestExit()**  
     ```c++
     //Request to exit the thread, the function returns immediately after sending the request but at this time, it does not mean 
     //that the thread has also exited
     my_thread.requestExit();
     ```

   위의 두 함수 중 하나를 호출 한 후 `threadLoop`함수에서 `bool exitPending()`멤버 함수를 사용하여 스레드 종료 요청이 있는지 확인할 수 있습니다.
   ```c++
   virtual bool threadLoop() {
       LOGD("Thread loop function");
       //Check if there is a request to exit the thread, if so, return false and exit the thread immediately
       if (exitPending()) {
           return false;
       }
       return true;
   }
   ```

   > [!Note]
   > 위의 함수는 thread를 강제로 종료하지 않고 thread 종료를 요청하는 표시를 추가합니다.
   > `threadLoop`함수에서 특정 작업을 수행하고 있고 `threadLoop`함수가 종료되지 않은 경우 thread가 중지되지 않습니다.
   > 올바른 접근 방식은 `threadLoop`에서 thread 종료 요청을 확인하거나 종료 조건을 확인한 다음 `false`를 반환하는 것입니다.

---
   > [!Warning]
   > `threadLoop`함수에서 `requestExitAndWait` 및 `requestExit` 함수를 호출하는 것은 교착 상태를 유발할 수 있어 금지되어 있습니다.

5. Thread가 실행 중인지 확인
   ```c++
   if (my_thread.isRunning()) {
     mTextView4Ptr->setText("Now running");
   } else {
     mTextView4Ptr->setText("Already stop");
   }
   ```

## Thread 프로세스
위의 단계를 순서도와 함께 이해하면 더 쉽고 깊게 이해가 가능합니다. 

![](images/threadloop.png)

## Sample code  
더 자세한 내용은 [Sample Code](demo_download.md#demo_download)의 `ThreadDemo` 프로젝트를 참고하십시오.  
    
![](assets/thread/example.png)

