
# <span id = "ftu_and_source_relationships">FlywizOSのコンパイルプロセスとUIファイルとソースコードの相関関係</span>
## UIファイルのコントロールがポインタ変数と接続されている方法
 FlywizOSは簡単な管理のためにUIとcodeを分離しました。
 下では、UIファイルは、プロジェクトのUIフォルダのすべてのftuファイルです。
 開発中のコードの重複を減らすために、FlywizOS IDEは、コンパイルプロセスを改善しました。実際のソースコードをコンパイルする前に、IDEは、まずUIファイルから生成された同じプレフィックス名を持つ`Logic.cc`ファイルを生成します。（例えば、`main.ftu`は`mainLogic.cc`ファイルが生成されます）。ここで、 `Logic.cc`ファイルの生成は、まさに上書きからではなく、徐々に修正されることに注意する必要があります。 
 コンパイル時、IDEは、各Uiファイルを巡回してUIファイルに含まれているコントロールを読んで、ソースコード上にコントロールするためのポインタ変数を定義し、開発者は、このポインタを利用して、対応するコントロールを制御することができます。このポインタ変数は、UIファイルと同じ接頭辞の名前を持つ`Activity.cpp`ファイルに定義されます。**main.ftu**を例に、以下の通りです。

![](assets/global_control_pointer.png)  

**上の図に示すように、すべてのポインタは、static global変数です。そして、それらはすべて同じ命名規則によって生成されました。この命名規則は、[コントロールのID名によるポインタ変数の命名規則](named_rule.md＃id_name_rule)を参照してください。 そして、上記の図では`#include" logic/mainLogic.cc"`にも注意すべきポイントです。`mainLogic.cc`は`mainActivity.cpp`に含まれます。開発者は、`mainLogic.cc`で必要なコーディングをし、すべてのコントロールのポインタ変数を使用することができます。**  
 もしこのポインタたちの初期化に興味がある場合`mainActivity`の`onCreate`関数を探してください。



## UIファイルとLogic.ccファイルの関係

 UIファイルのコントロールがどのようにポインタ変数と接続されるかについて調べてみました。今`mainLogic.cc`ファイルにどのようなものが自動的に生成されるかを知ってみましょう。
 もしUIファイルにはコントロールも追加していなかった場合、 `mainLogic.cc`ファイルは以下の通りです。

```c++ 
/**
 * Register timer
 * Fill the array to register the timer
 * Note: id cannot be repeated
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //Timer id=0, period 6 second
	//{1,  1000},
};

/**
 * Triggered when the interface is constructed
 */
static void onUI_init(){
    //Add the UI initialization display code here, for example :
    //mText1Ptr->setText("123");

}

/**
 * Triggered when switching to this interface
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * Triggered when the interface is displayed
 */
static void onUI_show() {

}

/*
 * Triggered when the interface is hidden
 */
static void onUI_hide() {

}

/*
 * Triggered when the interface completely exits
 */
static void onUI_quit() {

}

/**
 * Serial data callback interface
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * Timer trigger function
 * It is not recommended to write time-consuming operations in this function, otherwise it will affect UI refresh
 * Parameter : id
 *         The id of the currently triggered timer is the same as the id at registration
 * Return : true
 *             Keep running the current timer
 *         false
 *             Stop running the current timer
 */
static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}

/**
 * Triggered when there is a new touch event
 * Parameter : ev
 *         new touch event
 * Return : true
 *            Indicates that the touch event is intercepted here, and the system will no longer pass this touch event to the control
 *         false
 *            Touch events will continue to be passed to the control
 */
static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://Touch press
//			LOGD("event time = %ld axis  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://Touch move
			break;
		case MotionEvent::E_ACTION_UP:  //Touch up
			break;
		default:
			break;
	}
	return false;
}
```
 以下は、各関数について説明します。
* **REGISTER_ACTIVITY_TIMER_TAB[ ]  array**  
 [タイマーの登録](timer.md＃timer)に使用されます。この構造体の配列は以下の通りです。
```c++
typedef struct {
	int id; // Timer ID, cannot be repeated
	int time; // Timer interval, unit millisecond
}S_ACTIVITY_TIMEER;
```
 **この配列は、`void registerTimer(int id、int time)`関数を介してシステムに登録された後、`mainActivity.cpp`の` rigesterActivityTimer()`関数で参照されます。**

* **void onUI_init()**  
 アクティビティの初期化に使用されます。もしUIアクティビティの起動時に初期化が必要なコンテンツがある場合は、この関数にコードを追加することができます。 
この関数は、`mainActivity.cpp`の` onCreate()`関数で呼び出されます。

* **void onUI_quit()**  
 アクティビティの終了に使用されます。もしUIアクティビティの終了時にどのような作業が必要な場合は、この関数にコードを追加することができます。
この関数は、`mainActivity.cpp`の破壊者で呼び出されます。

* **void onProtocolDataUpdate(const SProtocolData &data)**  
 シリアルポートのデータの受信に使用されます。シリアルデータフレームが解析された後、この関数が呼び出されます。 
この関数は、`mainActivity.cpp`の` onCreate()`で`void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener)`を使用して登録され、`mainActivity.cpp`の破壊者で登録解除されます。詳細は、[シリアルフレームワーク](serial_framework.md)を参照してください。

* **bool onUI_Timer(int id)**  
 タイマーコールバック関数です。登録されたタイマーのタイマー周期が到達したとき、システムによって呼び出されます。 タイマーが複数登録されたならば、idパラメータで、各タイマを区別することができます。このidは** REGISTER_ACTIVITY_TIMER_TAB[] array**に登録されたidと同じです。  
Return `true`  このタイマーを維持 
Return `false` このタイマーを停止  
`false`を返して、タイマーを停止した場合はどのように再起動しますか？[タイマーを任意に開始および停止する方法](how_to_register_timer.md)を参照してください。

* **bool onmainActivityTouchEvent(const MotionEvent &ev)**  
 タッチイベントのコールバック関数です。すべてのタッチのメッセージを受信できます。
`mainActivity.cpp`の` registerGlobalTouchListener`を介して登録され、登録が完了した後になってようやくタッチイベントが受信されます。  
 Returning `true` タッチイベントがもう他のコントロールに渡されません。 
 Returning `false` タッチイベントが継続的に他のコントロールに渡されます。  
 [タッチイベントの処理の理解](motion_event.md)を参照してください。

以上は、基本的なUIのファイルがコンパイルされるときに自動的にLogic.ccファイルに生成されます。UIファイルにコントロールを追加し、コンパイルをする場合は、IDEは、該当するLogic.ccに異なるコントロールと関連付けられている関数を自動的に生成します。   
예를 들어, **main.ftu** UI 파일에 2 개의 단추 컨트롤을 추가하고 각 ID를`Button1`와`Button2`로 만들어 컴파일하면 아래의 두 가지 기능이 **mainLogic.cc** 파일 작성됩니다.

```c++
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}
```
関数の名前に注意してください。関数の名前は、コントロールのIDが含まれており、コントロールのIDは、C言語のネーミング標準に準拠する必要があります。もし継続的にコントロールを追加する場合は、追加されたコントロールに関連する関数は、コンパイル後に**mainLogic.cc**に生成されます。

一般的に開発している間に、UIファイルでコントロールの追加/削除/修正が非常に頻繁に起こるが、このような状況ではIDEは、以下のように動作します。
* コントロールを追加する場合 - IDE는 컴파일시 컨트롤의 ID에 따라 관련 함수를 작성하는데, 만약 같은 함수가 이미 존재하는 경우는 그 과정을 건너 뛰고 ** Logic.cc ** 파일은 변경되지 없습니다.
* コントロールを削除する場合 - UIファイルに存在するコントロールを削除しても関連する関数は削除されません。もし関連する関数も削除であれば、意図していないコードの損失が発生することができ、FlywizOS IDEは削除しないことを決定しました。
* コントロールを変更する場合 - 生成されたコントロール関連の関数は、唯一のコントロールのIDとのみ関連があります。もしUiファイルでコントロールのID以外のプロパティを変更する場合、これに関連する関数には影響を与えません。 もしコントロールのIDを変更した後、コンパイルをするなら、新たにコントロールを追加するのと同じプロセスが進行して、既存の関連する関数は維持されます。

**この章では、唯一のボタンコントロールに関連する例としてUIファイルのコントロールとLogic.ccに生成された関連する関数の関係についてのみ説明しました。FlywizOSはまた、他のコントロール（ex。Slide Bar、List、Slide Windowsなど）にも関連する関数を提供しています。詳細、他のコントロールに関連する関数について知りたい場合は、[コントロールによって自動的に生成された関数の関係の説明](named_rule.md＃relation_function)を参照してください。**

<br/>

**最後に、下の図は、ftuファイルとコードの間の相関関係を示す概略図である。**
![](assets/relationships.png)