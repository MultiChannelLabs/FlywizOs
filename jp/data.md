
## データストア

 特定のアプリケーションのシナリオでは、特定の情報（アカウント番号、パスワード、設定情報など）を永遠に保存する必要があります。これらのデータの特徴は、データ量が小さくてもアクセスが容易する必要があります。この場合、データベースを利用することなく、FlywizOSでは簡単に**key-valueの組み合わせ**形式でデータを保存する機能を提供します。

* 必要ヘッダファイル
  ```c++
    #include "storage/StoragePreferences.h"
  ```

* 関連する関数

  ```c++
    // Storage function
    static bool putString(const std::string &key, const std::string &val);
    static bool putInt(const std::string &key, int val);
    static bool putBool(const std::string &key, bool val);
    static bool putFloat(const std::string &key, float val);

    // Delete the specified key
    static bool remove(const std::string &key);
    // Clear storage data
    static bool clear();

    // Get function. The corresponding key value cannot be obtained, then the default value of defVal is returned
    static std::string getString(const std::string &key, const std::string &defVal);
    static int getInt(const std::string &key, int defVal);
    static bool getBool(const std::string &key, bool defVal);
    static float getFloat(const std::string &key, float defVal);
  ```

> [!Warning]
>  1. このインターフェイスは、フラッシュにデータをファイル形式で保存するので、**頻繁保存は、フラッシュの損傷を引き起こす可能性がありますので、避けるべきです。**
>  2. データを保存するためのパーティションのサイズは制限されています。モデルに応じてパーティションのサイズは異なりますが、512KBを超えないように維持することをお勧めします。

### 使用例
 * 保存

     ```c++
     //Save the string, use "username" as the alias, the value is the name string
     const char* name = "zhang san";
     StoragePreferences::putString("username", name);
     ```

     ```c++
     //Save the boolean variable, alias "power", the value is true
     StoragePreferences::putBool("power", true);
     ```

     ```c++
     //Save a floating point number, aliased to "temperature", the value is 30.12
     StoragePreferences::putFloat("temperature", 30.12);
     ```

     ```c++
     //Save the integer, use "age" as the alias, the value is 20
     StoragePreferences::putInt("age", 20);
     ```

 * 読む
   ```c++
     //Read the value of the "username" key, if there is no value, return an empty string
     std::string name = StoragePreferences::getString("username", "");
     //Log print the read string
     LOGD("username %s\n", username.c_str());
   ```
   ```c++
     //Read the Boolean variable, if there is no value, then specify to return false
     bool power = StoragePreferences::getBool("power", false);
   ```

     ```c++
     //Read floating-point number, if there is no value, specify to return 0
     float temperature = StoragePreferences::getFloat("temperature", 0);
     ```

     ```c++
     //Read floating-point number, if there is no value, specify to return 0
     int age = StoragePreferences::getInt("age", 18);
     ```

* 削除

    ```c++
    // Clear a value individually
    StoragePreferences::remove("username");
    StoragePreferences::remove("power");
    StoragePreferences::remove("temperature");
    StoragePreferences::remove("age");
    // Clear all values
    StoragePreferences::clear();
    ```

* 修正
  
  もし、特定の値を変更したい場合は、同じキーを使って新しい値を保存します。