# チェックボックス
 チェックボックスコントロールの基本は、ボタンコントロールです。もしスイッチボタンやチェックボタンのようにクリックするボタンの状態が変化し、クリックを解除しても、これを維持する必要がある場合は、チェックボックスコントロールを利用して、より簡単に実装可能です。



## 使い方

1. プロジェクトウィンドウで、チェックボックスを追加しようとするアクティビティのUIをダブルクリックします。

2. 右のコントロールボックスで`Checkbox`コントロールを選択します。

3. `Checkbox`コントロールをマウスの左クリックした後、ドラッグして、ボタンを作成する場所に置くと、自動的にコントロールが作成されます。

4. 作成されたボタンをマウスの左クリックすると、プロパティウィンドウで、ボタンに関連するプロパティを確認し、変更することができます。
   
   ボタンコントロールと同様に、画像の大きさは、基本的に、チェックボックスコントロールのサイズに沿っていき、必要に応じて位置とサイズを属性で調整可能です。
   ![](assets/checkbox/properties.png)   

5. プロパティの設定後、コンパイルすると、対応する`Logic.cc`ファイルに関連する関数が生成されます。そして、当該コントロールをクリック時に、システムで関連する関数を自動的に呼び出します。
   その関数のパラメータの中で`bool isChecked`は、コントロールの選択状態を表します。
   ```c++
   static void onCheckedChanged_Checkbox1(ZKCheckBox* pCheckBox, bool isChecked) {
     if (isChecked) {
       //Check box is selected
       LOGD("checked");
     } else {
       //Checkbox is unselected
       LOGD("unchecked");
     } 
   }
   ```

6. 実際のボードにダウンロードした後、テストしてみてください。


## 예제 코드

[Sample code](demo_download.md＃demo_download)のCheckBoxDemoプロジェクトを参照してください。 
サンプルコードの実行結果のプレビュー :   
![](assets/checkbox/example1.png)
![](assets/checkbox/example2.png)