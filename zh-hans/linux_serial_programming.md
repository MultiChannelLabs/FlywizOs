# Linux串口编程

> [!Note]
> **本篇文档旨在让大家理解FlywizOS项目串口部分的代码是如何从零到有的这个过程，从而更容易理解我们最终提供的串口部分代码流程。  
> 理解之后，您可以根据自己的需求任意修改源代码。**

该产品基于Linux系统，所以我们可以完全沿用标准Linux编程来操作串口。  
## 基本步骤
我将Linux串口编程分为以下5个步骤：**打开串口**、**配置串口**、**读串口**、**写串口**、**关闭串口**。
1. 打开串口
    ```c++
    #include <fcntl.h>
    ```
    ```c++
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    ```
    `open`是系统函数，负责打开某个节点  
    以上代码表示：以可读可写的方式，尝试打开`/dev/ttyS0`这个串口，如果打开成功，返回一个非负值，这个值表示串口描述符，若失败，返回一个负数，即错误码。  
    `/dev/ttyS0` 可以理解为串口号，类似Windows系统上的`COM1`。
    
2. 配置串口  
 成功打开串口后，还需要配置串口，设置波特率等参数。
 ```c++
 int openUart() {
      int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
      struct termios oldtio = { 0 };
      struct termios newtio = { 0 };
      tcgetattr(fd, &oldtio);
      //设置波特率为115200
      newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
      newtio.c_iflag = 0; // IGNPAR | ICRNL
      newtio.c_oflag = 0;
      newtio.c_lflag = 0; // ICANON
      newtio.c_cc[VTIME] = 0;
      newtio.c_cc[VMIN] = 1;
      tcflush(fd, TCIOFLUSH);
      tcsetattr(fd, TCSANOW, &newtio);

      //设置为非阻塞模式，这个在读串口的时候会用到
      fcntl(fd, F_SETFL, O_NONBLOCK);
      return fd;
}
 ```
 > [!Note]
 > 以上是本平台的默认串口配置，8个数据位，1个停止位，无校验。非特殊需求请勿修改，  
 > 受限于硬件与驱动，如果修改其为其他配置，可能会无效。
 
3. 读串口
  ```c++
   #include <fcntl.h>
  ```
  ```c++
  unsigned char buffer[1024] = {0};
  int ret = read(fd, buffer, sizeof(buffer));
  ```
  `read`是系统函数，它提供了读串口的功能，该函数需要三个参数：
   * 第一个参数 是串口描述符，即打开串口步骤中`open`函数的返回值。
   * 第二个参数 是缓冲区指针，用于保存读取的串口数据。
   * 第三个参数 是缓冲区长度，也表示本次最多能读取多少个字节。
  
  调用该函数，  
  如果返回值大于0，表示有正确收到串口数据，且返回值等于读取到数据量的字节数。  
  如果返回值小于或等于0， 表示有错误或者暂时没读到数据。
4. 发送串口
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
  `read`是系统函数，它提供了发送串口的功能，该函数需要三个参数：
   * 第一个参数 是串口描述符，即打开串口步骤中`open`函数的返回值。
   * 第二个参数 是待发送缓冲区指针。
   * 第三个参数 是待发送缓冲区长度
   
  调用该函数,
  如果返回值大于0， 且返回值等于传递的第三个参数，表示发送成功。  
  如果返回值小于或等于0，表示异常。
  
  > [!Note]
  > `read`函数只是顺序读取串口收到的数据流，但不能保证一次就读取完整的数据。  
  > 例如，短时间内，串口收到了1000个字节的数据，缓冲区的长度为1024，虽然1024 > 1000，   
  > 但可能我们第一次read后仅读取了一部分数据，所以我们需要多次read，才能保证数据读取完整。
5. 关闭串口
  ```c++
   #include <fcntl.h>
  ```
  ```c++
  close(fd);
  ```
`close`是系统函数，需要的参数是串口描述符，即打开串口步骤中`open`函数的返回值。

## 综合使用
以下是一个简单的Linux串口编程的完整例子，上面提到的几个基本步骤都有用到。  

```c++
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
  if (fd < 0) {
    //打开串口失败，退出
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
  //设置为非阻塞模式
  fcntl(fd, F_SETFL, O_NONBLOCK);

  while (true) {
    unsigned char buffer[1024] = {0};
    int ret = read(fd, buffer, sizeof(buffer));
    if (ret > 0) {
      //依次将读取到的数据输出到日志
      for (int i = 0; i < ret; ++i) {
        LOGD("收到%02x", buffer[i]);
      }

      //当收到数据时，再将收到的数据原样发送
      int n = write(fd, buffer, ret);
      if (n != ret) {
        LOGD("发送失败");
      }

      //当收到0xFF时，跳出循环
      if (buffer[0] == 0xFF) {
        break;
      }
    } else {
      //没收到数据时，休眠50ms，防止过度消耗cpu
      usleep(1000 * 50);
    }
  }

  close(fd);
  return 0;
}
```  

## 如何从软件上保证串口稳定通信
当我们将上面的例子尝试应用到正式产品的时候，会不可避免地遇到这些问题：
1. 串口通信可能会受到一定的干扰，她是不可靠的。  
  所以通常会制定通信协议， 这个协议一般包括**帧头**、**帧尾**、**帧内容**、**校验**等部分，  
  协议的使用可以最大程度地保证数据的完整性，使得串口通信变得可靠。
  
  举例：  
  如果我们定义协议， 以 `0xFF` `0x55`开头，后面跟上8个有效字节为完整的一帧。  
  那么上面Linux串口通信的例子的代码大概会修改成这样子：  
 
  ```c++
 //仅列出关键部分，其余代码省略
  while (true) {
    unsigned char buffer[1024] = {0};
    int ret = read(fd, buffer, sizeof(buffer));
    if (ret > 0) {

      if ((buffer[0] == 0xFF) && (buffer[1] == 0x55)) {
        if (ret == 10) {
          LOGD("正确读到一帧数据");
        } else if (ret < 10) {
          LOGD("协议头正确，但是帧长度错误");
        }
      }

      //当收到数据时，再将收到的数据原样发送
      int n = write(fd, buffer, ret);
      if (n != ret) {
        LOGD("发送失败");
      }

      //当收到0xFF时，跳出循环
      if (buffer[0] == 0xFF) {
        break;
      }
    } else {
      //没收到数据时，休眠50ms，防止过度消耗cpu
      usleep(1000 * 50);
    }
  }
  ```
  
2. 当我们将上面的代码用于实际测试，频繁的收发，很可能会遇到 **协议头正确，但是帧长度错误** 的情况。**为什么？**  
  因为Linux系统调度或其他的原因，`read`函数不能保证一次性将当时串口收到的所有数据都返回给你，  
  为了完整地读取串口数据，你需要多次调用`read`函数，然后将前后收到的数据拼接起来，再按协议校验数据，从中找到有效的帧。  
  虽然这么做代码变得复杂，但它是合理的。  
  根据刚才的分析，再将例子代码修改为这样子：  
  
  ```c++
  //提高buffer数组的作用域，使得while循环中不会清空数据
  unsigned char buffer[1024] = {0};
  // 增加一个`legacy`变量，表示buffer中遗留的数据长度
  int legacy = 0;
  while (true) {
    //根据legacy的大小，调整缓冲区的起始指针及大小，防止数据覆盖
    int ret = read(fd, buffer + legacy, sizeof(buffer) - legacy);
    if (ret > 0) {
      if ((buffer[0] == 0xFF) && (buffer[1] == 0x55)) {
        if ((ret + legacy) == 10) {
          LOGD("正确读到一帧数据");
          //清空legacy
          legacy = 0;
        } else if (ret < 10) {
          legacy += ret;
          LOGD("协议头正确，但是帧长度不够，则暂存在buffer里");
        }
      }

      //当收到数据时，再将收到的数据原样发送
      int n = write(fd, buffer, ret);
      if (n != ret) {
        LOGD("发送失败");
      }

      //当收到0xFF时，跳出循环
      if (buffer[0] == 0xFF) {
        break;
      }
    } else {
      //没收到数据时，休眠50ms，防止过度消耗cpu
      usleep(1000 * 50);
    }
  }
  ```

3. 实际应用中，我们不仅要处理串口通信，还要响应屏幕上各个按键等内容。  
  上面的例子中，从`main`函数开始，接着就是一个`while`循环，然后一直处理着串口消息，做不了其他事。  
  Linux系统支持 **多线程** ,通常，我们会新建一个子线程，再将这个`while`循环部分放到子线程中处理，这样就不会耽误我们继续其他操作。  
  如何修改，这里就不给出代码了。  
  
  
  
## 总结  
鉴于Linux上的串口通信编程，需要处理诸多细节的问题，FlywizOS提供了一份通用代码，它解决了如下问题：  
* 串口的打开、关闭、读写操作  
* 协议的拼接处理
* 提供统一的数据回调接口

这部分的源码是完全 **开源** 的，可以任意新建一个FlywizOS项目， 源码在项目的 **uart** 文件夹下。  
如果对比 **UartContext**类的源码，你应该可以从中看到本篇文档的影子。

希望可以通过本篇文档，可以让你熟悉FlywizOS项目的串口通讯部分的内容。
