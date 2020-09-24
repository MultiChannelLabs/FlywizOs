
## 데이타 저장소

 어떤 어플리케이션 시나리오에서는 특정 정보(계정 번호, 비밀번호, 설정 정보 등)를 영원히 저장할 필요가 있습니다. 이러한 데이타들의 특징은 데이타 양이 작지만 접근이 용이해야합니다. 이 경우 데이타베이스를 이용할 필요 없이 FlywizOS에서는 간단하게 **key-value 조합**형식으로 데이터를 저장할 수 있는 기능을 제공합니다.

* 필요 헤더 파일
  ```c++
    #include "storage/StoragePreferences.h"
  ```

* 관련 함수

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
>  1. 이 인터페이스는 플래시에 데이터를 파일 형태로 저장하므로 **잦은 저장은 플래시 손상을 유발할 수 있으니 지양해야 합니다.**
>  2. 데이터 저장을 위한 파티션의 크기는 제한되어 있습니다. 모델에 따라 파티션의 크기는 다르지만, 512KB를 넘지 않게 유지하는 것을 권장합니다.

### 사용 예제
 * 저장

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

 * 읽기
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

* 삭제

    ```c++
    // Clear a value individually
    StoragePreferences::remove("username");
    StoragePreferences::remove("power");
    StoragePreferences::remove("temperature");
    StoragePreferences::remove("age");
    // Clear all values
    StoragePreferences::clear();
    ```

* 수정  

  만약 특정 값을 수정하고 싶다면, 같은 키를 이용해 새로운 값을 저장합니다.