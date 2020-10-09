# Socket programming
만약 Linux socket programming에 익숙한 개발자라면 standard Linux socket programming interface에 따라 네트워크 프로그래밍을 할 수 있습니다.
예를 들어 TCP 클라이언트를 구축하기 위해 일반적으로 사용되는 소켓 프로그래밍 구현 작업의 경우 사용하기 편리한 Linux의 표준 인터페이스를 기반으로 간단한 패키지를 만들었습니다. 필요한 경우 단계에 따라 소스 코드를 프로젝트에 통합 할 수 있습니다.

## Porting steps  
1. 프로젝트의 jni폴더 아래에 새로운폴더를 만들고 이름을 `net`으로 합니다.   
    ![](assets/create_net_folder.png)   

2. [net.h](https://developer.flywizos.com/src/net/net.h), [net.cpp](https://developer.flywizos.com/src/net/net.cpp) 두 파일을 다운받아 `net` 폴더에 저장합니다.   
    ![](assets/net_class.png)  

## 사용법
### TCP Client
* 필요한 헤더 파일
  ```c++
  #include "net/net.h"
  ```
* 예제
  ```c++
  //Use TCP protocol to connect to port 80 of the domain name www.baidu.com, and change the domain name to IP.
  net::Conn* conn = net::Dial("tcp", "www.baidu.com:80");
  //net::Conn* conn = net::Dial("tcp", "14.215.177.38:80");
  if (conn) {
    byte buf[2048] = {0};
    const char* req = "GET / HTTP/1.1\r\nConnection: close\r\n\r\n";
    //send
    conn->Write((byte*)req, strlen(req));
    while (true) {
      //read，1000ms timeout
      int n = conn->Read(buf, sizeof(buf) - 1, 1000);
      if (n > 0) {
        buf[n] = 0;
        LOGD("read %d bytes： %s", n, buf);
      } else if (n == 0) {
        LOGD("Normal disconnection");
        break;
      } else if (n == net::E_TIMEOUT) {
        LOGD("read timeout");
      } else {
        LOGD("error");
        break;
      }
    }
    //Close the connection
    conn->Close();
    //Release memory
    delete conn;
    conn = NULL;
  ```

### UDP Client
* 필요한 헤더 파일
  ```c++
  #include "net/net.h"
  ```
* 예제
  ```c++
  //Use udp protocol to connect IP: 192.168.1.100 port 8080
  net::Conn* conn = net::Dial("udp", "192.168.1.100:8080");
  if (conn) {
    byte buf[2048] = {0};
    const char* req = "hello";
    conn->Write((byte*)req, strlen(req));
    while (true) {
      //read，1000ms timeout
      int n = conn->Read(buf, sizeof(buf) - 1, 1000);
      if (n > 0) {
        buf[n] = 0;
        LOGD("read %d bytes： %s", n, buf);
      } else if (n == 0) {
        LOGD("Normal disconnection");
        break;
      } else if (n == net::E_TIMEOUT) {
        LOGD("read timeout");
        //Set timeout here to exit
        break;
      } else {
        LOGD("error");
        break;
      }
    }
    //Close the connection
    conn->Close();
    //Release memory
    delete conn;
    conn = NULL;
  }
  ```

