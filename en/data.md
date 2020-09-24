
## Data storage

In some application scenarios, it is necessary to permanently store some information (save data after power off), such as account numbers, passwords, or other configuration information. The characteristics of these data are : the total amount is small, but it needs flexible access. In such cases, there is no need to use a database. We provide a simple data storage interface, which is stored in the form of **key-value pairs**.

* Required header files
  ```c++
    #include "storage/StoragePreferences.h"
  ```

* Main function

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
>  1. This function saves the data in the flash in the form of a file, so **do not write frequently to cause damage to the flash.**
>  2. The size of the partition is limited. The size of the partition varies depending on the model of the screen. Try to keep the data size within **512KB**.

### Usage example
 * Save

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

 * Read
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

* Delete

    ```c++
    // Clear a value individually
    StoragePreferences::remove("username");
    StoragePreferences::remove("power");
    StoragePreferences::remove("temperature");
    StoragePreferences::remove("age");
    // Clear all values
    StoragePreferences::clear();
    ```

* Modify

  If you need to modify a value, just save the key value repeatedly, and the old value will be automatically overwritten. 