# Linux serial programming
> [!Note]
> **이 챕터의 목적은 개발자에게 FlywizOS프로젝트의 시리얼 포트 파트의 코드를 이해시키는 것입니다.**
> **또한 우리는 개발자의 쉬운 이해를 위해 실제 코드로 해당 과정을 설명할 것이며, 이 과정이 끝나면 개발자들은 스스로 원하는대로 시리얼 포트를 수정할 수 있을 것입니다.**

FlywizOS는 Linux system을 기반으로 합니다. 따라서, 우리는 standard Linux programming operation으로 시리얼 포트를 사용할 수 있습니다.

## 기본 과정
우리는 Linux serial port programming을 5개의 과정으로 나누었습니다 : **open serial port**, **configure serial port**, **read serial port**, **write serial port**, **close serial port**.
1. Open serial port
    ```c++
    #include <fcntl.h>
    ```
    ```c++
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    ```
    `open`은 시스템 함수로, node의 오픈을 담당합니다.  
    위 코드의 의미는 : `/dev/ttyS0` 시리얼 포트를 readable/writable 속성으로 열기를 시도합니다. 만약 성공한다면 음수가 아닌 값을 리턴하고, 그 값은 시리얼 포트의 descriptor를 나타냅니다. 만약 실패한다면 음수를 리턴하고, 그 값은 error code입니다.  
    `/dev/ttyS0` 시리얼 포트의 번호로, 윈도우의 시스템의 `COM1`와 유사합니다.
    
2. Configure serial port  
   시리얼 포트 오픈 성공 후 Baud rate및 다른 파라미터들로 시리얼 포트를 설정해야합니다.
   ```c++
   int openUart() {
       int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
       struct termios oldtio = { 0 };
       struct termios newtio = { 0 };
       tcgetattr(fd, &oldtio);
       //Set the baud rate to 115200
       newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
       newtio.c_iflag = 0; // IGNPAR | ICRNL
       newtio.c_oflag = 0;
       newtio.c_lflag = 0; // ICANON
       newtio.c_cc[VTIME] = 0;
       newtio.c_cc[VMIN] = 1;
       tcflush(fd, TCIOFLUSH);
       tcsetattr(fd, TCSANOW, &newtio);

       //Set to non-blocking mode, this will be used when reading the serial port
       fcntl(fd, F_SETFL, O_NONBLOCK);
       return fd;
   }
   ```
   > [!Note]  
   > 위는 플랫폼의 기본 시리얼 포트 구성입니다. 특별한 경우가 아니라면 수정할 필요가 없습니다.  
   > 하드웨어와 드라이버의 한계로 수정하려고 하는 구성이 적합하지 않을 수도 있습니다.

3. Read serial port
   ```c++
   #include <fcntl.h>
   ```
   ```c++
   unsigned char buffer[1024] = {0};
   int ret = read(fd, buffer, sizeof(buffer));
   ```
   `read`는 시스템 함수로 시리얼 포트의 데이터를 읽는 함수입니다. 이 함수는 아래 3개의 파라미터가 필요합니다.
   * 첫 번째 파라미터는 시리얼 포트 descriptor로, `open`함수의 리턴 값입니다.
   * 두 번째 파라미터는 buffer포인터로 읽은 시리얼 데이터가 저장됩니다.
   * 세 번째 파라미터는 buffer의 크기로, 읽어들일 수 있는 데이터의 최대 값을 나타냅니다.

   만약 리턴 값이 0보다 크다면 시리얼 포트의 데이터를 정상적으로 읽었다는 의미이며 동시에 리턴값은 읽은 데이터의 byte수 입니다.  
   만약 리턴 값이 0보다 작거나 같다면, 데이터가 없거나 에러가 발생했다는 의미입니다.

   > [!Note]  
   > `read`는 오직 시리얼 포트로 수신된 순차적인 데이터만을 읽습니다. 그러나, 한 번에 모든 데이터를 읽어드리는 것을 보장하지는 않습니다. 
   > 예를 들어, 시리얼 포트로 1000bytes를 받았고, buffer의 크기가 1024로 비록 수신된 데이터보다는 크지만, 처음 `read` 시 오직 일부분만 읽어올 수 있어 모든 데이터를 읽기 위해서는 여러번에 걸쳐 `read`를 해야합니다.

4. Write serial port
   ```c++
   #include <fcntl.h>
   ```
   ```c++
   unsigned char buffer[4] = {0};
   buffer[0] = 0x01;
   buffer[1] = 0x02;
   buffer[2] = 0x03;
   buffer[3] = 0x04;
   int ret = write(fd, buffer, sizeof(buffer));
   ```
   `write`는 시스템 함수로, 시리얼 포트롤 데이터로 전송합니다. 이 함수는 아래 3개의 파라미터가 필요합니다. 
    * 첫 번째 파라미터는 시리얼 포트 descriptor로, `open`함수의 리턴 값입니다.
    * 두 번째 파라미터는 전송하려는 buffer의 포인터입니다.
    * 세 번째 파라미터는 전송하려는 buffer의 크기입니다.

   만약 리턴 값이 0보다 크다면 리턴 값은 세 번째 파라미터의 값과 같으며 전송 성공을 의미합니다.  
   만약 리턴 값이 0보다 작거나 같다면 예외가 발생했다는 의미입니다.

5. Close serial port
   ```c++
   #include <fcntl.h>
   ```
   ```c++
   close(fd);
   ```
   `close`는 시스템 함수이고, 필요한 파라미터는 시리얼 포트 descriptor입니다.

## 종합
아래는 간단한 Linux serial port programming의 예제입니다. 위에 언급했던 기본 기능이 모두 사용되었습니다.

```c++
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
  if (fd < 0) {
    //Failed to open the serial port, exit
    return -1;
  } 
  
  struct termios oldtio = { 0 };
  struct termios newtio = { 0 };
  tcgetattr(fd, &oldtio);

  newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = 0; // IGNPAR | ICRNL
  newtio.c_oflag = 0;
  newtio.c_lflag = 0; // ICANON
  newtio.c_cc[VTIME] = 0;
  newtio.c_cc[VMIN] = 1;
  tcflush(fd, TCIOFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);
  //Set to non-blocking mode
  fcntl(fd, F_SETFL, O_NONBLOCK);

  while (true) {
    unsigned char buffer[1024] = {0};
    int ret = read(fd, buffer, sizeof(buffer));
    if (ret > 0) {
      //Output the read data to the log in turn
      for (int i = 0; i < ret; ++i) {
        LOGD("Receive %02x", buffer[i]);
      }

      //When the data is received, send the received data as it is
      int n = write(fd, buffer, ret);
      if (n != ret) {
        LOGD("Failed to send");
      }

      //When receiving 0xFF, jump out of the loop
      if (buffer[0] == 0xFF) {
        break;
      }
    } else {
      //When no data is received, sleep for 50ms to prevent excessive consumption of cpu
      usleep(1000 * 50);
    }
  }

  close(fd);
  return 0;
}
```

## 소프트웨어에서 시리얼 포트의 안정적인 통신을 보장하는 방법
위의 방법을 적용하여 공식적인 제품을 개발할 때, 우리는 종종 아래와 같은 문제에 직면하게 됩니다.
1. 시리얼 통신은 간섭을 받을 수 있어 신뢰할 수 없습니다.  
   그러므로 정형화된 통신 프로토콜을 사용해야 합니다. 이 프로토콜은 일반적으로 **frame header**, **frame end**, **frame content**, **checkout**, 등을 포함합니다.  
   프로토콜을 사용하면 데이터의 무결성이 보장되어 시리얼 통신을 안정적으로 만들 수 있습니다.

   예 :  
   프로토콜의 프레임 헤더가 `0xFF`, `0x55`이고, 뒤의 8bytes로 프레임이 완성된다면, 위의 코드는 아마도 아래처럼 수정될 것입니다.
   ```c++
   //Only the key parts are listed, the rest of the code is omitted
   while (true) {
     unsigned char buffer[1024] = {0};
     int ret = read(fd, buffer, sizeof(buffer));
     if (ret > 0) {
       if ((buffer[0] == 0xFF) && (buffer[1] == 0x55)) {
         if (ret == 10) {
           LOGD("Read a frame of data correctly");
         } else if (ret < 10) {
           LOGD("The protocol header is correct, but the frame length is wrong");
         }
       }

       //When the data is received, send the received data as it is
       int n = write(fd, buffer, ret);
       if (n != ret) {
         LOGD("Failed to send");
       }

       //When receiving 0xFF, jump out of the loop
       if (buffer[0] == 0xFF) {
         break;
       }
     } else {
       //When no data is received, sleep for 50ms to prevent excessive consumption of cpu
       usleep(1000 * 50);
     }
   }
   ```

2. 위의 코드로 실제 빈번히 데이터를 주고 받는 테스트를 하면, **프로토콜 헤더는 맞지만 프레임의 크기가 틀린 경우**를 자주 보게 될 것입니다. 그 이유는 아마 Linux system scheduling에 있거나, 다른 곳에 있을 것입니다. `read`함수는 한 번에 모든 데이터를 읽는 것을 보장하지 않습니다. 모든 데이터를 읽어드리기 위해서는 여러차례 `read`함수를 호출해야 하고, 이는 프레임 데이터가 나누어져 읽혀지기 때문에 프로토콜에 맞게 하나의 유효한 프레임을 찾아야 합니다. 이를 위해 코드가 조금 더 복잡해 지겠지만, 이는 필요한 과정입니다.
   이러한 분석에 근거하여 수정된 코드는 아래와 같습니다. 
    ```c++
    //Increase the scope of the buffer array so that the data will not be cleared in the while loop
    unsigned char buffer[1024] = {0};
    // Add a `legacy` variable to indicate the length of data left in the buffer
    int legacy = 0;
    while (true) {
      //According to the size of the legacy, adjust the start pointer and size of the buffer to prevent data overwriting
      int ret = read(fd, buffer + legacy, sizeof(buffer) - legacy);
      if (ret > 0) {
        if ((buffer[0] == 0xFF) && (buffer[1] == 0x55)) {
          if ((ret + legacy) == 10) {
            LOGD("Read a frame of data correctly");
            //clean legacy
            legacy = 0;
          } else if (ret < 10) {
            legacy += ret;
            LOGD("The protocol header is correct, but the frame length is not enough, it is temporarily stored in the buffer");
          }
        }

        //When the data is received, send the received data as it is
        int n = write(fd, buffer, ret);
        if (n != ret) {
          LOGD("Failed to send");
        }

        //When receiving 0xFF, jump out of the loop
        if (buffer[0] == 0xFF) {
          break;
        }
      } else {
        //When no data is received, sleep for 50ms to prevent excessive consumption of cpu
        usleep(1000 * 50);
      }
    }
    ```

3. 실제 제품에서 우리는 시리얼 통신만을 처리하는 것이 아니라, 화면상의 여러 컨트롤 등에 대한 처리도 필요합니다. 위의 예제는 `main`함수에서 시작되고, `while`루프에서 시리얼 데이터를 처리하기 때문에 다른 처리를 할 수가 없습니다. 그러나 Linux system은 **multithreading**기능을 지원하기 때문에 새로운 thread를 만들고, 그 thread에 `while`루프 부분을 넣는다면, 동시에 다른 컨트롤들에 대한 처리도 가능해질 것입니다.

## 요약
Linux의 시리얼 통신 프로그래밍을 할 때 많은 세부 문제들을 처리해야 합니다. 그리고, FlywizOS에서는 문제 해결을 위해 일반 코드를 제공합니다. 
* 시리얼 포트의 open, close, read, write operations
* 나뉘어진 프로토콜 데이터에 대한 처리
* 통합 데이터 콜백 인터페이스 제공

이 챕터의 소스코드는 **open source**입니다. 개발자가 새로운 FlywizOS프로젝트를 만들면 프로젝트의 **uart**폴더에 이 코드가 있을 것입니다.