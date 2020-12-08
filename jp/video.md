# Video view
FlywizOSは動画のプレイのためのコントロールも提供しています。

> [!Note]
> 動画プレイ機能は、すべてのバージョンの機器でサポートされていません！この機能を正常に使用するには、マルチメディア機能があるバージョンをご購入下さい。

## コントロールのLoopプロパティの操作方法
1. まず、**Video View**コントロールを作成します。既定の背景色は黒です。

2. **Video view**のプロパティ]ウィンドウを確認します。  
   ![](assets/video/properties.png)  

    そのうちの一つの属性に**Loop**があります。
    そのプロパティを**Yes**を選択すると、UIアクティビティに入るたびに、自動的にTFカードのディレクトリ構成ファイルを読み取り、ファイルに指定されたドンヨウンサンルル繰り返しプレイします。アクティビティを終了すると、自動的にプレイを停止します。この属性は、広告装置のように、短い動画の自動プレイなど、ユーザーの介入なしに動画のみプレイする必要があるデバイスに非常に適しています。  
    **No**を選択すると、動画のレンダリング領域のみ生成され、他のタスクは実行されません。その後、直接操作して動画をプレイする必要があります。

3. 動画構成ファイルの作成
  前述したよう**Loop**が**Yes**の場合の動画構成ファイルを自動的に読み取ります。(ファイルは直接作成します。) この構成ファイルは、TFカードのルートディレクトリにする必要があり、ファイル名は、**XXXX_video_list.txt**です。XXXXは、UIファイル名を表します。例：**main.ftu**にVideo Viewコントロールを追加すると、その構成ファイルの名前は、**main_video_list.txt**です。構成ファイルは、行単位で、各ラインは、動画ファイルの絶対パスです。動画ファイルがTFカードのルートディレクトリにある場合、`/mnt/extsd/`を入力して、動画ファイルの名前を追加します。  
  ![](assets/video/video_list.png)

   **Note：ファイル名のエンコードの問題に起因する動画ファイルの読み取りの失敗を防止するには、動画ファイルの名前を英語で指定します。**

4. プログラムが実行された後、構成ファイルのドンヨウンサンルル自動的に繰り返しプレイすることができます。

## 指定された動画ファイルのプレイ
1. **Video View**コントロールを作成します。
2. `Loop`をNoに設定します。
3. プレイを制御するためのコードを追加します。

  Play
  ```c++
  //Play the test.mp4 file, starting from time 0
  mVideoView1Ptr->play("/mnt/extsd/test.mp4", 0);
  ```
  Pause
  ```c++
  //Pause playback
  mVideoView1Ptr->pause();
  ```
  Resume
  ```c++
  //Resume playback
  mVideoView1Ptr->resume();
  ```
  Stop
  ```c++
  mVideoView1Ptr->stop();
  ```
  特定の時間に移動した後プレイ
  ```c++
  //Jump to the 10 second position
  mVideoView1Ptr->seekTo(10 * 1000);
  ```
  プレイ音量の設定、範囲0〜1.0
  ```c++
  //Set the volume to 0.5
  mVideoView1Ptr->setVolume(0.5);
  ```
  プレイしていることを確認
  ```c++
  bool state = mVideoView1Ptr->isPlaying();
  if （state) {
    LOGD("Now Playing");
  }
  ```
  動画の総プレイ時間（ms）を取得します。
  ```c++
  int n = mVideoView1Ptr->getDuration();
  ```

  動画の現在のプレイ位置をms単位で取得します。
  ```c++
  int n = mVideoView1Ptr->getCurrentPosition();
  ```
  
  動画は非同期的にプレイされ、自動的に生成された関連機能が動画プレイの状態をお知らせします。
  ```c++
    static void onVideoViewPlayerMessageListener_VideoView1(ZKVideoView *pVideoView, int msg) {
        switch (msg) {
        case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
          LOGD("Start playback");
            break;
        case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
          LOGD("End playback");
            break;
        case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
          LOGD("Error");
            break;
        }
    }
  ```

## 完全なビデオプレーヤーの実装
動画プレイのためのより高い要件がある場合プレイ/一時停止、および現在のプレイ時間などを操作することができる必要があります。 
[すべての動画プレーヤーのサンプル（続き）]()を参照してください。

## Sample code
詳細については、[Sample Code](demo_download.md＃demo_download)のVideDemoプロジェクトを参照してください。

![](assets/video/preview.png) 