# Multiple serial port configuration

Conventional projects only support one serial port by default. If you want to use dual serial ports or even multiple serial ports, please download [DoubleUartDemo sample](demo_download.md#demo_download). In this example, part of the serial port code is modified in the conventional project to support multiple serial ports.

## Change
The changes are described below.
* Some codes of uart have been modified, so the serial port configuration in the project properties is invalid.
* Please refer to the `init()` function in the `jni/uart/UartContext.cpp` file to modify the serial port number and baud rate.
  ~~~C++
  void UartContext::init() {
      uart0 = new UartContext(UART_TTYS0);
      uart0->openUart("/dev/ttyS0", B9600);

      uart1 = new UartContext(UART_TTYS1);
      uart1->openUart("/dev/ttyS1", B9600);
}
  ~~~

* Send data to the designated serial port

  ~~~C++
      unsigned char buf[2] = {1, 1};
      sendProtocolTo(UART_TTYS1, 1, buf, 2); //Send to TTYS1 serial port
  
      unsigned char buf[2] = {0};
      sendProtocolTo(UART_TTYS0, 1, buf, 2);//Send to TTYS0 serial port
  ~~~
  
* The method of receiving serial port data is the same as that of regular projects  
  If you need to distinguish which serial port the data comes from, it is recommended to add a field to the `SProtocolData` structure to identify which serial port the frame comes from.
  
  Change `uart/ProtocolData.h`
  ~~~C++
  typedef struct {
	    BYTE power;
	    int uart_from; //From which serial port
} SProtocolData;
  ~~~

  Change `uart/ProtocolParser.cpp`

  ~~~C++
    /**
     * Analyze each frame of data
     */
    static void procParse(int uart, const BYTE *pData, UINT len) {
        // CmdID
        switch (MAKEWORD(pData[3], pData[2])) {
        case CMDID_POWER:
            sProtocolData.power = pData[5];
            break;
        }

        sProtocolData.uart_from = uart; //Identify which serial port the frame comes from
        // Notify protocol data update
        notifyProtocolDataUpdate(sProtocolData);
    }
  ~~~

   Then in `Logic.cc`, you can use the `uart_from` field to determine which serial port the data comes from.
  
   ~~~C++  
 static void onProtocolDataUpdate(const SProtocolData &data) {
      LOGD("onProtocol %d", data.uart_from);

      char buf[128] = {0};
      snprintf(buf, sizeof(buf), "Receive serial port %d data", data.uart_from);
      mTextview1Ptr->setText(buf);
}
   ~~~
  
  ## Sample code
    For the complete code, see the `DoubleUartDemo` project in [Sample Code](demo_download.md#demo_download)