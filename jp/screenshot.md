# スクリーンショット
製品開発の後マニュアル作成時に実行されているインターフェースのスクリーンショットが必要な場合があり、下のスクリーンショットコードを参照してください。
## Ready
1. [screenshot.h](https://developer.flywizos.com/src/screenshot.h)ソースファイルをダウンロードして、プロジェクト`jni`ディレクトリに保存します。
    ![](assets/screenshot1.png)

## Use

* 必要なヘッダファイル
  ```c++
  #include "screenshot.h"
  ```
* 関数を呼び出して、スクリーンショットを撮る
  ```c++
  static bool onButtonClick_Button1(ZKButton *pButton) {
    //Capture the current screen, save it as a bmp picture, and save it to the TF card directory
    //Each time this function is called, the name of the saved picture is incremented
    //Example - screenshot01.bmp、screenshot02.bmp、screenshot03.bmp
    Screenshot::AutoSave();
    return false;
  }
  ```
  写真は基本的にTFカードに保存されるので、TFカードを挿入して、スクリーンショットを撮りなさい。
  別の場所に保存する必要がある場合は、ソースコードを直接変更することができます。 
