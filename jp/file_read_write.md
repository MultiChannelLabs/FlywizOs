# File read/write
 もし、C言語のFile read/ writeに慣れている場合は、C言語のスタンダードでFile read/ writeが可能です。

 簡単File read/ writeのために我々は、C言語でも提供されている簡単なFile read/ writeパッケージを提供しています。もし必要であれば、以下のプロセスをプロジェクトに追加します。


```c++
/**
 * Write a file. If the file exists, it will be overwritten. If the file does not exist, create a new file and write the content
 * Successfully returned true
 */
bool WriteFile(const char* filename, const void* data, int len);

/**
 * Append content at the end of the file, if the file does not exist, create a new file first, and then write the content
 * Successfully returned true
 */
bool AppendFile(const char* filename, const void* data, int len);

/**
 * Read file
 * Success - save the file in the data of string in binary form, read the binary content with string.data()
 * Failure - Return empty string
 */
string ReadFile(const char* filename);
```

## Porting steps 
1. プロジェクトのjniフォルダに`io`フォルダを作成  
    ![](assets/create_io_folder.png)
2. [ioutil.h](https://www.flywizos.com/src/io/ioutil.h), [ioutil.cpp](https://www.flywizos.com/src/io/ioutil.cpp)をダウンロードして`io`フォルダに保存   
    ![](assets/ioutil.png)  


## 使い方
* Include header file
  ```c++
  #include "io/ioutil.h"
  ```
* Write file
  ```c++
  //Write the string "0123456789" into the file 123.txt
  const char* filename = "/mnt/extsd/123.txt"; //Path to save the file
  const char* str = "0123456789";
  ioutil::WriteFile(filename, str, strlen(str));
  ```

* Append file
  ```c++
  //Append the content to the end of the file, if the specified file does not exist, create a new file.
  const char* append_str = "abcdefgh";
  ioutil::AppendFile(filename, append_str, strlen(append_str));
  ```
  
* Read file
  ```c++
  const char* filename = "/mnt/extsd/123.txt";
  //Read all the contents of the file and save it in content
  string content = ioutil::ReadFile(filename);
  //Output each byte read to the log in hexadecimal
  for (size_t i = 0 ; i < content.size(); ++i) {
    LOGD("%02d byte = 0x%02X", i, content.data()[i]);
  }
  ```
  > [!Warning]
  > `ioutil::ReadFile関数は、ファイルのすべての内容をメモリに読み込みます。もし、ファイルが大きすぎると、メモリ不足の例外が発生します。


* Write file continuously, suitable for large file
  ```c++
  const char* filename = "/mnt/extsd/123.txt";
  const char* append_str = "abcdefgh";
  ioutil::Writer w;
  if (w.Open(filename, false)) {
    for (int i = 0; i < 5; ++i) {
      w.Write(append_str, strlen(append_str));
      w.Write("\n", 1);
    }
    w.Close();
  }
  ```

* Read file continuously, suitable for large file
  ```c++
  const char* filename = "/mnt/extsd/123.txt";
  ioutil::Reader r;
  if (r.Open(filename)) {
    char buf[1024] = {0};
    while (true) {
      int n = r.Read(buf, sizeof(buf));
      if (n > 0) {
        //Have read content, output every byte
        for (int i = 0; i < n; ++i) {
          LOGD("%02x", buf[i]);
        }
      } else if (n == 0) {
        //End of reading file
        break;
      } else {
        //Error
        break;
      }
    }
    r.Close();
  }
  ```



## Test code  
```c++
/**
 * Triggered when the interface is constructed
 */
static void onUI_init() {
  //Write file
  const char* filename = "/mnt/extsd/123.txt";
  const char* str = "0123456789";
  ioutil::WriteFile(filename, str, strlen(str));
  string content = ioutil::ReadFile(filename);
  LOGD("Number of bytes read %d, content:%s", content.size(), content.c_str());
  //Append file
  const char* append_str = "abcdefgh";
  ioutil::AppendFile(filename, append_str, strlen(append_str));
  content = ioutil::ReadFile(filename);
  LOGD("Number of bytes read %d, content:%s", content.size(), content.c_str());

  ioutil::Writer w;
  if (w.Open(filename, false)) {
    for (int i = 0; i < 5; ++i) {
      w.Write(append_str, strlen(append_str));
      w.Write("\n", 1);
    }
  }
  w.Close();

  ioutil::Reader r;
  if (r.Open(filename)) {
    char buf[1024] = { 0 };
    while (true) {
      int n = r.Read(buf, sizeof(buf));
      if (n > 0) {
        //Have read content, output every byte
        for (int i = 0; i < n; ++i) {
          LOGD("%02x", buf[i]);
        }
      } else if (n == 0) {
        //End of reading file
        break;
      } else {
        //Error
        break;
      }
    }
    r.Close();
  }

  content = ioutil::ReadFile(filename);
  LOGD("Number of bytes read %d, content:%s", content.size(), content.c_str());

  //If it is a read binary file, not text, you should get the binary like this
  //Output each byte in hexadecimal
  for (size_t i = 0; i < content.size(); ++i) {
    LOGD("%02d byte = 0x%02X", i, content.data()[i]);
  }
}
```