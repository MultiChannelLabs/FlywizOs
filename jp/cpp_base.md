# C++基本的な知識
 この章では、C++の基本的な知識がない人にC ++の基本的な構文とクラスについて説明します。

## Class
 C ++の場合は、まず**class**を言及する必要があります。あまりにも複雑であると考えていないC言語のstructureに理解するようにします。 
 例えば、:

```c++
// C
struct Position {
	int left;
	int top;
	int width;
	int height;
};

// c++
class Position {
public:
	int left;
	int top;
	int width;
	int height;
};
```
変数の定義 :

```c++
// C
struct Position pos;

// c++
Position pos;
```
変数操作 :

```c++
// C is the same as c++
pos.left = 0;
```
 **class**は、C言語の構造よりも相続、ポリモーフィズム、オーバーロードおよびアクセス権の概念があります。Cに慣れている人は、これをどのように使用するかは十分に知るためには、そうでない場合は、多くの努力を払う必要がありません。
 さらに、C言語では、関数ポインタのみ定義が、C++の**class**は、関数を直接実装が可能です。この部分がCとは異なる点で、**class**に定義された関数は、一種の変数のように使用されます。以下は、頻繁に使用されている例です。

```c++
// Set the text content, where mTextView1Ptr is a pointer variable of type ZKTextView
mTextView1Ptr->setText("Hello");
```

## 基本 class
### string class
string classは、実際のstringとこれのために提供されている多くの関数がカプセル化されています。しかし、Cに慣れているユーザーは、`c_str()`関数だけ分かっても、十分に活用できます。この関数は、string classからcharactersだけを返す関数として以下のように使用することができます。

```c++
// Input box callback function
static void onEditTextChanged_Edittext1(const std::string &text) {
	// The return value type of c_str() function : const char *
	const char *pStr = text.c_str();
	
	// Then you can operate like ordinary strings, such as getting the string length strlen(pStr), etc.
	
}
```
以下は、テキストコントロールのテキストを取得例です。

```c++
// std is the namespace, std::string means to use the string class under std, don’t worry too much 
// When encountering the string class, we can refer to the following definition
std::string text = mTextView1Ptr->getText();

// The subsequent operations are the same
const char *pStr = text.c_str();
```


## <span id="snprintf">snprintf</span>
### 関数のプロトタイプ :
  ```c++
  int snprintf(char* dest_str,size_t size,const char* format,...);
  ```
### 機能 : 
  複数のパラメータを定められたフォーマットに合わせてstring化してdest_strに保存
  (1) もしformatted stringのlengthがsizeよりも小さい場合stringがコピーされ、stringの終わりに'\0'が追加されます。
  (2) もしformatted stringのlengthがsize以上の場合のみsize-1のstringだけコピーされ、最後に'\ 0'が追加されます。

### 必要ヘッダファイル :
  ```
  #include <stdio.h>
  ```

### フォーマット形式
* Specifier  
  `%d` Decimal signed integer  
  `%u` Decimal unsigned integer  
  `%f` Floating point  
  `%s` String  
  `%c` Character  
  `%p` Pointer value  
  `%e` Exponential floating point  
  `%x`, %X Unsigned integer in hexadecimal  
  `%o` Unsigned integer in octal  
  `%g` Output the value according to the smaller output length in %e or %f type  
  `%p` Output address  
  `%lu` Output long integer
  `%llu` 64-bit unsigned integer   
* Description  
    (1) 最大フィールド幅を示すために"％"と文字の間に数字を挿入することができます。
    例：％3dは3つの整数の出力を意味します。3桁のができないなら、右に配置されます。
    ％9.2fはフィールドの幅が9である浮動小数点数を表します。ここで、小数点以下の桁は2であり、整数桁は6です。小数点が一桁で、9桁のができないなら、右に配置されます。
    ％8sは8文字の文字列を出力することを意味し、8文字できないなら右揃えされます。
    文字列の長さや整数の数が指定されたフィールドの幅を超えた場合、実際の長さに応じて出力されます。
    しかし、浮動小数点数の場合は、整数の数が指定された整数の幅を超えると、実際の整数で出力されます。
    小数点以下の桁数が指定された小数点以下の桁数を超えると、指定された幅に応じて出力が丸められます。
    また、出力値の前に0を追加するには、フィールドの幅用語の前に0を追加する必要があります。
    例：％04dは、4桁の未満の値を出力するときにゼロが追加され、合計の幅が4桁がされることを意味します。
    浮動小数点数を使用して文字または整数の出力形式を表す場合は、小数点の後の数字は最大幅を示し、小数点の前の数字は、最小幅を表します。
    例：％6.9sは、長さが6以上9以下の文字列を表示することを意味します。9を超える場合は、9番目の文字以降の内容は削除されます。
    (2) "％"と文字の間に小文字lを追加して、出力が長い数字であることを示すことができます。
    例：％ldはlong出力を意味します。
    ％lfは出力double-float数を意味します。
    (3) 出力を左揃えまたは右揃えに制御することができます。つまり、「％」と文字の間に「 - 」の記号を追加して、出力が左揃えされることを示し、それ以外の場合右揃えされます。
    例：％-7dは出力7つの整数が左寄せされることを意味します。
    ％-10sは左揃えされた10文字の出力を意味します。
* Special specifier  
  `\n` 改行  
  `\f` 画面を消去し、ページ変更 
  `\r` キャリッジリターン  
  `\t` Tab

### 例
  * 整数出力
  ```c++
  char buf[64] = {0};
  snprintf(buf, sizeof(buf), "%d", 314);
  LOGD("%s", buf);//Log output buf
  ```
  出力されたlog :
  ```
  314
  ```

  * 整数の桁数を指定出力
  ```c++
  char buf[64] = {0};
  snprintf(buf, sizeof(buf), "%05d", 314); //Format as 5 digits, less than 5 digits, add 0 in front
  LOGD("%s", buf);//Log output buf string
  ```
  出力されたlog :  
  ```
  00314
  ```
  * 浮動小数点出力
  ```c++
  char buf[64] = {0};
  snprintf(buf, sizeof(buf), "%f", 3.14); 
  LOGD("%s", buf);//Log output buf string
  ```
  出力されたlog :  
  ```
  3.140000
  ```

  * 浮動小数点以下の桁を指定出力
  ```c++
  char buf[64] = {0};
  //Output decimals, a total of 6 characters wide (including the decimal point), 3 decimal places, two integer digits, and 0 if   //the integer is less than two digits
  snprintf(buf, sizeof(buf), "%06.3f", 3.14);
  LOGD("%s", buf);//Log output buf string
  ```
  出力されたlog :  
  ```
  03.140
  ```
