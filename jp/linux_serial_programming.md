# Linux serial programming

> [!Note]
> **この章の目的は、開発者にFlywizOSプロジェクトのシリアルポートパーツのコードを理解させることです。**
> **また、私たちは、開発者の簡単な理解のために、実際のコードでは、プロセスを説明するものであり、このプロセスが完了したら、開発者は、自ら必要に応じて、シリアルポートを変更することができるでしょう。**

FlywizOSはLinux systemに基づいています。したがって、我々はstandard Linux programming operationにシリアルポートを使用することができます。

 

## 基本的なプロセス
 私たちは、Linux serial port programmingを5つのコースに分けました : **open serial port**, **configure serial port**, **read serial port**, **write serial port**, **close serial port**.
1. Open serial port
    ```c++
    #include <fcntl.h>
    ```
    ```c++
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    ```
    `open`はシステム関数で、nodeのオープンを担当します。
    위 코드의 의미는 : 上記のコードの意味は：シリアルポート`/dev/ttyS0`をreadable/ writable属性で開くしようとします。 もし成功すれば負でない値を返し、その値は、シリアルポートのdescriptorを表します。もし失敗した場合負の値を返し、その値はerror codeです。  
    `/dev/ttyS0`はシリアルポートの番号では、Windowsのシステムの`COM1`と似ています。
    
2. Configure serial port  
 シリアルポートのオープンに成功した後、シリアルポートのBaud rateおよび他のパラメータを設定する必要があります。
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
 > 上記は、プラットフォームのデフォルトのシリアルポート設定です。特別な場合を除き、変更する必要がありません。  
 > ハードウェアとドライバの限界として使用しようとする構成が適していないことがあります。

3. Read serial port
  ```c++
   #include <fcntl.h>
  ```
  ```c++
  unsigned char buffer[1024] = {0};
  int ret = read(fd, buffer, sizeof(buffer));
  ```
  `read`は、システム関数でシリアルポートのデータを読み取る関数です。この関数は、以下の3つのパラメータが必要です。
   * 最初のパラメータは、シリアルポートdescriptorに、`open`関数の戻り値です。
   * 第二のパラメータは、bufferポインタで読んだシリアルデータが格納されます。
   * 第三パラメータはbufferの大きさで、読み込めるデータの最大値を示します。

 もし戻り値が0よりも大きい場合、シリアルポートのデータを正常に読んだという意味であり、同時に戻り値は、読み取ったデータのbyte数です。  
 もし戻り値が0よりも小さいか同じであれば、データがない場合、またはエラーが発生したことを意味します。

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
  `write`はシステム関数で、シリアルポートロールのデータを転送します。この関数は、以下の3つのパラメータが必要です。
   * 最初のパラメータは、シリアルポートdescriptorに、`open`関数の戻り値です。
   * 第二のパラメータは、送信しようとするbufferのポインタです。
   * 第三パラメータは、伝送しようとするbufferのサイズです。

 もし戻り値が0よりも大きい場合、戻り値は、第三のパラメータの値と同じで転送成功を意味します。  
 もし戻り値が0よりも小さいか同じであれば、例外が発生したことを意味します。

  > [!Note]
  > `read`はただのシリアルポートで受信された連続的なデータのみを読み取ります。しかし、一度にすべてのデータを読み取る届けを保証しません。
  > たとえば、シリアルポートに1000bytesを受け、bufferのサイズが1024でたとえ受信されたデータではなく大きいが、最初に`read`時ただ一部分のみ読み込むことができ、すべてのデータを読むためには、何度も`read`をしなければならします。
5. Close serial port
  ```c++
   #include <fcntl.h>
  ```
  ```c++
  close(fd);
  ```
`close`はシステム関数であり、必要なパラメータは、シリアルポートdescriptorです。

## 総合
 以下は簡単なLinux serial port programmingの例です。上記した基本的な機能がすべて使用されました。

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



## ソフトウェアでシリアルポートの信頼性の高い通信を確保するための方法

 上記の方法を適用して正式な製品を開発するとき、私たちはしばしば次のような問題に直面します。
1. シリアル通信は、干渉を受けることができていて、信頼できません。
    したがって、定型化された通信プロトコルを使用します。このプロトコルは、一般的に**frame header**、**frame end**、**frame content**、**checksum**、などが含まれています。
    プロトコルを使用すると、データの整合性が確保されてシリアル通信を安定的に行うことができます。

 例 :  
  プロトコルのフレームヘッダが`0xFF`、`0x55`であり、後の8bytesにフレームが完成であれば、上記のコードは、おそらく次のように修正されます。

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

2. 上記のコードで実際頻繁にデータを送受信するテストするとき、**プロトコルヘッダは合っているが、フレームのサイズが間違っている場合**をよく見るようになります。 
    その理由は、おそらくLinux system schedulingにあるか、他の所であるでしょう。`read`関数は、一度にすべてのデータを読み取ることを保証しません。すべてのデータを読み取るいただくためには、何回も`read`関数を呼び出す必要があり、これはフレームのデータが分かれて読まれるため、これをプロトコルに合わせて一つの有効なフレームを見つける必要があります。このため、コードがもう少し複雑だろうが、これは必要なプロセスです。  
    これらの分析に基づいて修正されたコードは以下の通りです。

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

3. 実際の商品では、シリアル通信のみを処理するのではなく、画面上の複数のコントロールなどの処理も必要です。  
    上記の例では、`main`関数で開始され、`while`ループでシリアルデータを処理するため、他の処理をすることができません。
    しかし、Linux systemは**multithreading**機能をサポートするため、私たちは新しいthreadを作り、そのthreadに`while`ループ部分を入れる場合は、同時に他のコントロールに対する処理も可能になるでしょう。

  

## 要約
 Linuxのシリアル通信のプログラミングをするとき、多くの詳細な問題を処理する必要があります。また、FlywizOSは、トラブルシューティングのために一般的なコードを提供しています。
* シリアルポートのopen、close、read、write operations
* 分割されたプロトコルデータの処理
* 統合データコールバックインターフェースを提供

 この章のソースコードは、** open source**です。開発者が新しいFlywizOSプロジェクトを作成するときに、プロジェクトの** uart**フォルダにこのコードがあるでしょう。