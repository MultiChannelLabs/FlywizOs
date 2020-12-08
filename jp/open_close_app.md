 先に我々はすでに開始アクティビティについて学びました。開始アクティビティの実行後2番目、3番目のステップの他のアクティビティを実行することができます。次に、他のアクティビティを実行して終了する方法について学ぶようにします。

## Application activity 実行
 たとえば今**sub.ftu**に対応するアクティビティを実行する必要があります。先に開始アクティビティの分析に応じて、UIリソースに対応するアクティビティオブジェクトが**subActivity**であることを知ることができます。これらはIDEによって自動的にコードです。私たちは、ここであまりにも多くの細部に注意を払う必要がなく、簡単にイエてはと、次のコードでアクティビティを開始することができます。 

```c++
EASYUICONTEXT->openActivity("subActivity");
```
 もしボタンクリックスルー**sub.ftu**アクティビティに入るには、ボタンのクリックイベント関数では、上記の関数を呼び出します。
```c++
static bool onButtonClick_Button1(ZKButton *pButton) {
    // Jump to the sub.ftu activity 
    EASYUICONTEXT->openActivity("subActivity");
    return false;
}
```
 通常の状況下では、上記の呼び出しコードで十分です。しかし、支払いページのようにアクティビティの間どのような情報を渡す必要がある場合は、openActivityに渡される2番目のパラメータを使用して情報を伝達する必要があります。
```c++
Intent *pIntent = new Intent();
pIntent->putExtra("cmd", "open");
pIntent->putExtra("value", "ok");
EASYUICONTEXT->openActivity("subActivity", pIntent);
```
 **subLogic.cc**の`onUI_intent`コールバックで受信することができます。
```c++
static void onUI_intent(const Intent *intentPtr) {
	if (intentPtr) {
		// Key value analysis
		std::string cmd = intentPtr->getExtra("cmd");		// "open"
		std::string value = intentPtr->getExtra("value");	// "ok"
		......
	}
}
```
Note：   
	1. 新しいインテントは、手動で削除する必要がありませんフレームワーク内で自動的に削除されます。   
	2. putExtraはstringのkey-value pairメソッドのみを提供します。intまたは他のタイプの値を渡す必要がある場合、文字列型に変換し、onIntentから受信した後、変換を実行する必要があります。

## Application activity 終了</span>
 上記のopenActivity関数を使用してsubActivityを実行したところ、元のアクティビティに戻りたい場合はどうでしょうか？  
 次のコードを使用して、以前のアクティビティに戻ることができます。

```c++
EASYUICONTEXT->goBack();
```
 ボタンによってgoBack()がトリガされる場合には、IDEを使用して、ボタンのID値を`sys_back`に設定すると、直接goBack（）機能を使用することができます。

![](images/Screenshotfrom2018-06-06220522.png)


 もし、より階層的なアクティビティに開始アクティビティに戻ろう場合は、次のコードで実装可能です。

```c++
EASYUICONTEXT->goHome();
```
 開始アクティビティに戻ります。
 また、ボタンでトリガされる場合は、IDEを使用して、ボタンのID値を`sys_home`に設定すると、直接goHome（）機能を使用することができます。
 最後に、EasyUIContextのcloseActivity関数を使用してアクティビティを終了することもできます。たとえばsubActivityを終了したい場合は、以下のようにすることができます。

```c++
EASYUICONTEXT->closeActivity("subActivity");
```
 この関数を使用するには、呼び出し元が終了するアクティビティの名前を知っている。 
 Note : この関数は、開始アクティビティを終了することができません。開始アクティビティは常に存在します。