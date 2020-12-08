# シリアルポートを構成する方法
## シリアルポート番号を選択

ソフトウェアとハードウェアの設計の互換性のためにソフトウェアのシリアル番号がハードウェアのシリアル番号の識別と異なる場合があります。具体的な関係は、次のとおりです。

* F9311s Series platform

| Software serial port number | Hardware serial port number |
|:--------:|:-------:|
| ttyS0   | UART1  |
| ttyS1   | UART2  |

* F9306 Series platform

| Software serial port number | Hardware serial port number |
|:--------:|:-------:|
| ttyS0   | UART0  |
| ttyS1   | UART1  |
| ttyS2   | UART2  |

## シリアルポートBaud rate構成
1. 新しいプロジェクトを作成するときにBaud rateを設定します。

  ![](images/730034409.jpg)

2. プロジェクトのプロパティでBaud rate構成
    プロジェクトを右クリックし、ポップアップメニューからPropertyを選択すると、次のプロパティボックスが表示されます。

  ![](images/918330052.jpg)

## シリアルポートを開くと閉じる
jni/Main.cppを開きます。プログラムが初期化されて終了したとき、シリアルポートが開閉を見ることができます。

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