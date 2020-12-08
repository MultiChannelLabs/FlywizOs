# カメラ
 FlywizOSは、カメラコントロール機能を提供します。

> [!Note]
>  すべてのバージョンのボードからカメラ機能をサポートしていません。もしこの機能が必要な場合は、USBカメラ機能をサポートしているボードを購入する必要があります。

## 使い方
1. まず、カメラコントロールを作成します。デフォルトの背景は黒です。
2. カメラコントロールのプロパティ]ウィンドウを確認します。

   ![](assets/camera/properties.png)  

  Auto Preview属性を**On**に設定します。 
  接続されているカメラのタイプに応じて、**CVBS Signal**属性を選択します。

3. カメラウルボードに接続し、プログラムをダウンロードすると、カメラから入力される映像を見ることができます。

   

## プレビュー開始/停止
ソースコードを使用してプレビューの開始/停止を制御することができます。
* プレビュー開始
```c++
mCameraView1Ptr->startPreview();
```
* プレビュー停止
```c++
mCameraView1Ptr->stopPreview();
```

## プレビュー画面キャプチャ

1. カメラコールバックインターフェイスの実装
  ```c++
  class PictureCallback : public ZKCamera::IPictureCallback {
  public:
      virtual void onPictureTakenStarted() {
        mTextView1Ptr->setText("Start taking a photo");
      }
      virtual void onPictureTakenEnd() {
        mTextView1Ptr->setText("End of photo");
      }
      virtual void onPictureTakenError() {
        mTextView1Ptr->setText("Photo error");
      }
      virtual const char* onPictureSavePath() {
          //Photo save path
          return "/mnt/extsd/camera.jpg";
      }
  };
  ```

2. カメラコールバックインターフェース宣言
  ```c++
  //Defined as a global static variable
  static PictureCallback picture_callback;
  ```

3. カメラコントロールのインターフェースの登録と登録解除
  ```c++
  static void onUI_init(){
      mCameraView1Ptr->setPictureCallback(&picture_callback);
  }
  ```
  ```c++
  static void onUI_quit() {
    //Remember to empty the registration interface when the interface exits
      mCameraView1Ptr->setPictureCallback(NULL);
  }
  ```
4. ボタンを追加して、ボタンが押される時の画面キャプチャ
  ```c++
  static bool onButtonClick_Button3(ZKButton *pButton) {
	  //Request a photo
	  mCameraView1Ptr->takePicture();
      return false;
  }
  ```

## サンプルコード
この例では、カメラのプレビュー、キャプチャ機能などが実装されています。

[Sample code](demo_download.md＃demo_download)のCameraDemoプロジェクト参照してください。

![](assets/camera/preview.png) 