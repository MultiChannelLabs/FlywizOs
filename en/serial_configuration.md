# How to configure the serial port
## Selection of serial port number

Due to the design compatibility of software and hardware, the serial number of the software may be different from the serial number identification on the hardware. The specific correspondence is as follows :

* Z11 Series platform

| Software serial port number | Hardware serial port number |
|:--------:|:-------:|
| ttyS0   | UART1  |
| ttyS1   | UART2  |

* Z6 Series platform

| Software serial port number | Hardware serial port number |
|:--------:|:-------:|
| ttyS0   | UART0  |
| ttyS1   | UART1  |
| ttyS2   | UART2  |

* A33 Series platform

| Software serial port number | Hardware serial port number |
|:--------:|:-------:|
| ttyS1   | UART1  |
| ttyS2   | UART2  |
| ttyS3   | UART3  |

## Serial port baud rate configuration
1. Configure the baud rate when creating a new project 

  ![](images/730034409.jpg)

2. Project properties to modify the baud rate
    Right-click the project, select the Properties in the pop-up box, and the following properties box will pop up 

  ![](images/918330052.jpg)

## Serial port open and close
Open the source "jni/Main.cpp"; we can see that the serial port is opened and closed when the program is initialized and destroyed.

```c++
void onEasyUIInit(EasyUIContext *pContext) {
    LOGD("onInit\n");
    // open serial port
    UARTCONTEXT->openUart(CONFIGMANAGER->getUartName().c_str(), CONFIGMANAGER->getUartBaudRate());
}

void onEasyUIDeinit(EasyUIContext *pContext) {
    LOGD("onDestroy\n");
    // close serial port
    UARTCONTEXT->closeUart();
}
```