# 複数のシリアルポートを構成する

 基本的に作成されたプロジェクトは、1つのシリアルポートのみをサポートしますが、必要に応じて2つまたはそれ以上のシリアルポートを使用することができます。まず、[DoubleUartDemo例](demo_download.md＃demo_download)をダウンロードしてください。この例では、複数のシリアルポートをサポートしているプロジェクトについてのコードが含まれています。

## 変更
変更は以下の通りです。
* Uartのいくつかのコードが変更されました。だからproject propertiesで設定した属性は、もはや有効ではありません。

* 使用するシリアルポートの番号とBaudrateは`jni/uart/UartContext.cpp`ファイルの`init()`関数を参考にして修正してください。
  ~~~C++
  void UartContext::init() {
      uart0 = new UartContext(UART_TTYS0);
      uart0->openUart("/dev/ttyS0", B9600);

      uart1 = new UartContext(UART_TTYS1);
      uart1->openUart("/dev/ttyS1", B9600);
}
  ~~~

* シリアルポートにデータを送信します。

  ~~~C++
      unsigned char buf[2] = {1, 1};
      sendProtocolTo(UART_TTYS1, 1, buf, 2); //Send to TTYS1 serial port
  
      unsigned char buf[2] = {0};
      sendProtocolTo(UART_TTYS0, 1, buf, 2);//Send to TTYS0 serial port
  ~~~
  
* シリアルポートのデータを受信する方法は、既存のプロジェクトと同じです。  
  もしどこから来たシリアルポートのデータなのか区別する必要がある場合は、 `SProtocolData` structureにメンバ変数を追加して区別をすることができます。  
  `uart/ProtocolData.h`変更
  
  ~~~C++
  typedef struct {
	    BYTE power;
	    int uart_from; //From which serial port
  } SProtocolData;
  ~~~

  `uart/ProtocolParser.cpp`変更

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

   `Logic.cc`で`uart_from`フィールドを確認して、どのシリアルポートから受信したデータであることを決定することができます。
  
   ~~~C++  
   static void onProtocolDataUpdate(const SProtocolData &data) {
      LOGD("onProtocol %d", data.uart_from);

      char buf[128] = {0};
      snprintf(buf, sizeof(buf), "Receive serial port %d data", data.uart_from);
      mTextview1Ptr->setText(buf);
  }
   ~~~
  
  ## サンプルコード
  [サンプルコード](demo_download.md#demo_download)の`DoubleUartDemo`プロジェクトを参照してください。