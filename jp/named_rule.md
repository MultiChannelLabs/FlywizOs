# Naming ルール
 UIファイルに追加したほとんどのコントロールは、コンパイル後の関連ポインタ変数とマクロIDが自動的に生成されます。
## <span id="id_name_rule">コントロールIDとポインタ変数の名前のためのNamingルール</span>

 ポインタ変数の名前は、それぞれ固定された小文字prepix**m**+**ID**の値+**Ptr**の三つのパートで構成されます。  
 IDで** Textview1**を持つコントロールを例に説明します。

![Textview1](assets/textview/Textview1.png) 

 コンパイル後に生成されるポインタ変数の名前は、**`mTextview1Ptr`**です。

![mTextview1Ptr](assets/textview/mTextview1Ptr.png)  

 ポインタ変数のclassは、コントロールによって決定されます。各コントロールに対応するポインタclassは以下の通りです。（プロジェクトの**jni/ include**フォルダで、各classのヘッダファイルを見つけることができます。）

| Control name | Class name 
|:--------:|:-------:
| ![](assets/qrcode/icon.png)   | ZKQRCode  | 
| ![](assets/edittext/icon.png)   | ZKEditText   |
| ![](assets/button/icon.png)   | ZKButton    |
| ![](assets/textview/icon.png)    | ZKTextView   |
| ![](assets/seekbar/icon.png)   | ZKSeekBar   | 
| ![](assets/pointer/icon.png)   | ZKPointer   | 
| ![](assets/circlebar/icon.png)   | ZKCircleBar   | 
| ![](assets/clock/icon.png)   | ZKDigitalClock   | 
| ![](assets/video/icon.png)   | ZKVideoView   | 
| ![](assets/camera/icon.png)   | ZKCameraView   | 
| ![](assets/window/icon.png) | ZKWindow |
|  ![](assets/list/icon.png)| ZKListView |
|  ![](assets/slidewindow/icon.png) | ZKSlideWindow |
|  ![](assets/diagram/icon.png) | ZKDiagram |

## <span id="id_macro_rule">コントロールIDとmacro definitionのnamingルール</span>
 このmacro definitiondは、UIファイルでコントロールのマッピング関係を示します。
 Macro definitionは、固定された大文字`ID`、大文字UIファイル名、コントロールID propertyの値の3つの部分で構成されます。  
 IDを**Textview1**と持つコントロールの例をみましょう。

![Textview1](assets/textview/Textview1.png) 

コンパイル後、生成されたmacro statementは **#define ID_MAIN_TextView150001**です。

![](assets/id_macro.png)

> [!Warning]
> Macro definitionの値を変更しないでください。非正常動作の原因になることがあります。

## <span id = "relation_function">コントロールによって生成される関連関数</span>
 特定のコントロールは、関連付けられている関数を自動的に生成します。以下は、これらのコントロールによって自動的に生成された関数について説明します。
> [!Note]
>  **関数で`XXXX`は、コントロールのID値です。**

* ### Button コントロール
   ```c++
   static bool onButtonClick_XXXX(ZKButton *pButton) {
      return false;
   }
   ```
   ボタンがクリックされると呼び出される関数です。
   
     * パラメータ`ZKButton* pButton`はクリックされたボタンのポインタであり、ポインタのメンバ変数を使用して、一連のoperationを行うことができます。このポインタは、グローバル変数`mXXXXPtr`が指すオブジェクトと同じオブジェクトのポインタです。

* ### Edit Text コントロール
  ```c++
  static void onEditTextChanged_XXXX(const std::string &text) {
    
  }
  ```
Input boxが変更されたとき、システムによって自動的に呼び出される関数です。
  
  * パラメータ`std::string＆text`は、現在Input boxのcontentsです。
  
* ### Seek Bar コントロール
  ```c++
  static void onProgressChanged_XXXX(ZKSeekBar *pSeekBar, int progress) {
  
  }
  ```
 Seek Barのプログレス値が変更されると、システムによって自動的に呼び出される関数です。
  * パラメータ`ZKSeekBar* pSeekBar`はSeek Barのポインタ変数であり、ポインタのメンバ変数を使用して、一連のoperationを行うことができます。  
  * パラメータ`int progress`は、現在Seek Barのプログラス値です。

* ### <span id = "slidewindow"> Slide window コントロール</span>
  ```c++
  static void onSlideItemClick_XXXX(ZKSlideWindow *pSlideWindow, int index) {
    
  }
  ```
  
  Slide windowコントロールのアイコンがクリックされたとき、システムによって自動的に呼び出される関数です。
  
    * パラメータ`ZKSlideWindow* pSlideWindow`はSlide windowコントロールのポインタ変数であり、ポインタのメンバ変数を使用して、一連のoperationを行うことができます。  
    * パラメータ`int index`は、現在クリックされたアイコンのindex値です。たとえば、Slide windowに合計10個のアイコンを追加した場合index値の範囲は[0、9]です。
  
* ### <span id = "list">List コントロール</span>   
リストコントロールは、最も複雑なコントロールで三つの関連関数を生成します。しかし、多くの関数がありますが、次の手順に従えば簡単に理解することができます。   
  1. まず、もしシステムがリストコントロールを描画たい場合、どのように多くのアイテムがあるか知る必要があります。  
     以下はそれに関連する関数です。   
     ```c++
     static int getListItemCount_XXXX(const ZKListView *pListView) {
      
           return 0;
     }
     ```
     * パラメータ`const ZKListView* pListView`はListコントロールのポインタであり、グローバル変数` mXXXXPtr`と同じオブジェクトを指します。
     * **戻り値**は整数であり、リストにあるアイテムの数を示し、必要に応じて決定されます。

  2. システムがリストのアイテム数を知っているたが、これだけでリストを描画には不足して、各アイテムにどのようなコンテンツをピョヒすべきかも知っている。だから下の関数があります。表示するアイテムの数だけ下の関数が呼び出され、表示する内容を設定することになります。
     ```c++
     static void obtainListItemData_XXXX(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
         //pListItem->setText(index)
     }
     ```
     * パラメータ`ZKListView* pListView`はListコントロールのポインタであり、グローバル変数`mXXXXPtr`と同じオブジェクトを指します。

     * パラメータ`ZKListView:: ZKListItem* pListItem`は、リストアイテムのポインタであり、UIファイルの`Item`に対応します。

     * パラメータ`int index`は全体のリストから`pListItem`のindex値です。  
      **例:** `getListItemCount_XXXX`関数の戻り値が10という意味ではリストに10個のアイテムがあり、`index`値の範囲が[0、9]ということです。  
      `pListItem`と` index`を接続して、全体のリストから任意のアイテムを設定する必要があるか知ることができます。
     
     この関数では`index`に基づいて、各アイテムに表示されるコンテンツが設定されることがあります。      

  3. ボタンコントロールと同様に、リストコントロールもクリックイベントのための関数を持っており、index値に基づいて、現在どのようなアイテムがクリックされたかを判断します。
     ```c++
     static void onListItemClick_XXXX(ZKListView *pListView, int index, int id) {
         //LOGD(" onListItemClick_ Listview1  !!!\n");
     }
     ```
     リストコントロールがクリックされると、システムは、クリックされた位置に対応するアイテムのindex値を計算して、自動的にこの関数を呼び出します。
     * パラメータ`ZKListView* pListView`はListコントロールのポインタであり、グローバル変数` mXXXXPtr`と同じオブジェクトを指します。 
     * パラメータ`int index`は全体のリストコントロールで現在クリックされたアイテムのindex値です。
     * パラメータ`int id`は、現在クリックされたコントロールのIDです。このIDは、propertiesのIDと異なるので注意してください。  

     これに対するmacro definitionは、対応する`Activity.h`ファイルにあります。`mainActivity.h`を例に示します。   

     ![](assets/ID-Macro1.png)  

     このIDは、list itemに複数のsubitemがある場合は、現在クリックされたsubitemがどんなものかを区別するために使用することができます。  
     **例：** 下の図に示すように、list itemにスイッチイメージが配置された2つのsubitemが追加されており、それぞれのproperty IDは`SubItem1`と`SubItem2`です。`SubItem1`がクリックされたとき、パラメータ` id`と `ID_MAIN_SubItem1`そして` ID_MAIN_SubItem2`の関係で判断されるものでいくつかのスイッチがクリックされたかを決定することができます。
     ```c++
     static void onListItemClick_XXXX(ZKListView *pListView, int index, int id) {
          //LOGD(" onListItemClick_ Listview1  !!!\n");
        switch(id) {
        case ID_MAIN_SubItem1:
            //LOGD("Clicked the first subitem of item %d in the list", index);
            break;
        case ID_MAIN_SubItem2:
            //LOGD("Clicked the second subitem of item %d in the list", index);
            break;
        }
     }
     ```

     ![](assets/ListView-tree.png) 

     ![](assets/ListView-subitem.png)

**最後に、図を用いて、それらの間のルールを要約してみましょう。**

![](assets/named_rule.png)

他のコントロールもこれと同じです。
