# Linux serial programming

> [!Note]
> **The purpose of this document is to let everyone understand how the code of the serial port part of the FlywizOS project went from zero to something. It is easier to understand the code flow of the serial port part we finally provide.  
> After understanding, you can modify the source code according to your needs.**

This product is based on the Linux system, so we can completely use standard Linux programming to operate the serial port.  
## The basic steps
We divide Linux serial port programming into the following 5 steps: **open serial port**, **configure serial port**, **read serial port**, **write serial port**, **close serial port**.
1. Open serial port
    ```c++
    #include <fcntl.h>
    ```
    ```c++
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    ```
    `open` is a system function, responsible for opening a node  
    The above code means: try to open the `/dev/ttyS0` serial port in a readable and writable manner. If it is opened successfully, it returns a non-negative value, which represents the serial port descriptor. If it fails, it returns a negative number, which is an error code. .  
    `/dev/ttyS0` It can be understood as a serial port number, similar to `COM1` on Windows systems.
    
2. Configure serial port  
 After successfully opening the serial port, you need to configure the serial port and set the baud rate and other parameters.
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
 > The above is the default serial port configuration of this platform, with 8 data bits, 1 stop bit, and no check. Do not modify for non-special needs.  
 > Limited by hardware and drivers, if you modify it to other configurations, it may be invalid.

3. Read serial port
  ```c++
   #include <fcntl.h>
  ```
  ```c++
  unsigned char buffer[1024] = {0};
  int ret = read(fd, buffer, sizeof(buffer));
  ```
  `read` is a system function, which provides the function of reading the serial port. This function requires three parameters:
   * The first parameter is the serial port descriptor, which is the return value of the `open` function in the step of opening the serial port.
   * The second parameter is the buffer pointer, which is used to save the read serial data.
   * The third parameter is the length of the buffer, which also indicates the maximum number of bytes that can be read this time.

  Call the function,  
  If the return value is greater than 0, it means that the serial port data has been received correctly, and the return value is equal to the number of bytes of data read.  
  If the return value is less than or equal to 0, it means there is an error or no data is read temporarily.

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
  `write` is a system function, which provides the function of sending serial port. This function requires three parameters :
   * The first parameter is the serial port descriptor, which is the return value of the `open` function in the step of opening the serial port.
   * The second parameter is the pointer to the buffer to be sent.
   * The third parameter is the length of the buffer to be sent

   Call the function,
  If the return value is greater than 0, and the return value is equal to the third parameter passed, it means the transmission was successful.  
  If the return value is less than or equal to 0, it means an exception.

  > [!Note]
  > The `read` function only reads the data stream received by the serial port sequentially, but it cannot guarantee that the complete data will be read once.  
  > For example, in a short time, the serial port receives 1000 bytes of data, and the length of the buffer is 1024, although 1024> 1000,   
  > but maybe we only read part of the data after the first read, so we need to read multiple times to ensure that the data is read completely.
5. Close serial port
  ```c++
   #include <fcntl.h>
  ```
  ```c++
  close(fd);
  ```
`close` is a system function, and the required parameter is the serial port descriptor, that is, the return value of the `open` function in the step of opening the serial port.

## Comprehensive use
The following is a complete example of a simple Linux serial port programming. The basic steps mentioned above are all used.  

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

## How to ensure stable communication of serial port from software
When we try to apply the above examples to official products, we will inevitably encounter these problems:
1. Serial communication may be disturbed to some extent, and it is unreliable.  
    Therefore, a communication protocol is usually formulated. This protocol generally includes **frame header**, **frame end**, **frame content**, **checkout**, etc.  
    The use of the protocol can ensure the integrity of the data to the greatest extent, making the serial port communication reliable.

 For example:  
  If we define the protocol, it starts with `0xFF` and `0x55`, followed by 8 valid bytes for a complete frame.  
  Then the code of the Linux serial communication example above will probably be modified to look like this :

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

2. When we use the above code for actual testing and frequent sending and receiving, it is very likely that the **protocol header is correct, but the frame length is wrong**. **why? **  
    Because of Linux system scheduling or other reasons, the `read` function cannot guarantee that all data received by the serial port will be returned to you at one time.  
    In order to read the serial port data completely, you need to call the `read` function multiple times, then splice the received data before and after, and then verify the data according to the protocol to find a valid frame.  
    Although the code becomes complicated to do so, it is reasonable.  
    Based on the analysis just now, modify the example code to look like this :  

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

3. In actual applications, we not only have to deal with serial communication, but also respond to the various buttons on the screen.  
    In the above example, it starts with the `main` function, followed by a `while` loop, and then processes the serial port messages all the time, and cannot do other things.  
    The Linux system supports **multithreading**. Usually, we will create a new child thread, and then put this `while` loop part in the child thread for processing, so that we will not delay our other operations.  
    How to modify, the code is not given here.  

  

## Summary
In view of the serial communication programming on Linux, many detailed problems need to be dealt with, FlywizOS provides a general code, which solves the following problems : 
* Open, close, read and write operations of serial port 
* Splicing of protocol
* Provide a unified data callback interface

The source code of this part is completely **open source**, you can create a new FlywizOS project at will, the source code is in the **uart** folder of the project.  If you compare the source code of the **UartContext** class, you should be able to see the shadow of this document. 
 I hope that through this document, you can be familiar with the serial communication part of the FlywizOS project.