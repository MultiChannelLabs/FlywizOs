# 다중 시리얼 포트 구성
기본적으로 만들어지는 프로젝트는 오직 하나의 시리얼 포트만을 지원하지만, 필요한 경우 2개 또는 그 이상의 시리얼 포트를 사용할 수 있습니다. 먼저 [DoubleUartDemo 예제](demo_download.md#demo_download)를 다운로드 하십시오. 이 예제 안에 다중 시리얼 포트를 지원하는 프로젝트에 관한 코드가 담겨있습니다.

## 변경 사항
변경 사항은 아래와 같습니다.
* Uart의 몇몇 코드들이 수정되었습니다. 그래서 project properties에서 설정한 속성은 더 이상 유효하지 않습니다.

* 사용하는 시리얼 포트의 넘버와 Baud rate는  `jni/uart/UartContext.cpp`파일의 `init()`함수를 참고해서 수정하십시오.
  ~~~C++
  void UartContext::init() {
      uart0 = new UartContext(UART_TTYS0);
      uart0->openUart("/dev/ttyS0", B9600);

      uart1 = new UartContext(UART_TTYS1);
      uart1->openUart("/dev/ttyS1", B9600);
  }
  ~~~

* 시리얼 포트로 데이타를 보냅니다.
  ~~~C++
  unsigned char buf[2] = {1, 1};
  sendProtocolTo(UART_TTYS1, 1, buf, 2); //Send to TTYS1 serial port

  unsigned char buf[2] = {0};
  sendProtocolTo(UART_TTYS0, 1, buf, 2);//Send to TTYS0 serial port
  ~~~
  
* 시리얼 포트 데이터를 받는 방법은 기존 프로젝트와 동일합니다.  
  만약 어디에서 온 시리얼 포트 데이타인지를 구분할 필요가 있다면 `SProtocolData` structure에 멤버 변수를 추가하여 구분을 할 수 있습니다.  
  `uart/ProtocolData.h`변경  
  ~~~C++
  typedef struct {
	    BYTE power;
	    int uart_from; //From which serial port
  } SProtocolData;
  ~~~

  `uart/ProtocolParser.cpp`변경
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

  `Logic.cc`에서 `uart_from`필드를 확인하여 어떤 시리얼 포트로부터 수신된 데이타인지 판단할 수 있습니다.  
  ~~~C++  
  static void onProtocolDataUpdate(const SProtocolData &data) {
      LOGD("onProtocol %d", data.uart_from);

      char buf[128] = {0};
      snprintf(buf, sizeof(buf), "Receive serial port %d data", data.uart_from);
      mTextview1Ptr->setText(buf);
  }
  ~~~
  
## 예제 코드
[예제 코드](demo_download.md#demo_download)의 `DoubleUartDemo`프로젝트를 참고하십시오.