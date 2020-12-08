
# View log
## Log 追加
* 必要なヘッダファイル
  ```c++
  #include "utils/Log.h"
  ```
  FlywizOSは`LOGD`または` LOGE`マクロを使用して、ログを出力します。使用方法は、C言語の`printf`と同じです。  
  以下は自動的に生成されたコードの例です。
  
    ```c++
    static bool onButtonClick_Button1(ZKButton *pButton) {
        LOGD("onButtonClick_Button1\n");
        return true;
    }
    ```

## ログの確認

[ADB](adb_debug.md)）接続後、ツールを介してプログラムのログを確認することができます。方法は以下の通りです。

1. メニューから**FlywizOS** - >**Show Log Perspective**を選択すると、IDEは、別の画面に切り替えます。
    ![](assets/ide/log_perspective.png)

2. 新しい画面の左下で**LogCat**を選択します。もし正常であれば、右の赤い色ボックス領域から出力されるログを確認することができます。
    ![](assets/ide/log_view.png)   
    もしコーディング画面に切り替えるしたい場合は、IDEの右上の**FlywizOS**アイコンをクリックしてください。
    ![](assets/ide/perspective_fly.png)