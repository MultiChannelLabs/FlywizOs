# QR code
## QR codeを追加する方法
 QR codeを表示する必要がある場合は、既存の「QR code」コントロールを使用して迅速に実装できます。具体的な手順は次のとおりです。

1. ダブルクリックしてUIファイルを開きます。
2. 右側のコントロールボックスで`QR code`コントロールを検索します。
3. `QR code`コントロールをマウスの左ボタンで押したまま、目的の場所にドラッグした後、左のボタンを離すと、QR codeコントロールが作成されます。
4. 作成したQR codeコントロールを選択した後、右側の[プロパティ]ウィンドウで、QR codeの内容を変更して、QR code画像が同時に変更されることがわかります。

   ![](assets/QrCode-create.gif)

## QR codeを動的に更新
IDEを使用してQR codeコンテンツを設定することに加え、コードを介してQR codeコンテンツを動的に設定することもできます。 
```c++
bool loadQRCode(const char *pStr);
```
# Sample code
 ![](assets/qrcode/preview.png)  

詳細は、[Sample Code](demo_download.md＃demo_download)のQrCodeDemoプロジェクトを参照してください。