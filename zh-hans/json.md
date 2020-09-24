# JSON的构造与解析

默认项目的已经包含开源`cppjson`库，可直接使用。  

## 使用步骤
### 引用头文件
```c++
#include "json/json.h"
```

### 构造JSON字符串
```c++
Json::Value root;
//添加整型值
root["int"] = 1;
//添加字符串
root["str"] = "hello";

//由于浮点数存在精度打印问题，不推荐使用，尽量转为整型
root["float"] = 3.14f;

//添加数组
Json::Value array;
array.append("123");
array.append("456");
array.append("789");
root["array"] = array;

//json的嵌套
Json::Value sub;
sub["int"] = 1;
sub["str"] = "sub str value";
root["subJson"] = sub;

LOGD("生成的json字符串为: ");
LOGD("%s", root.toStyledString().c_str());
```

### 解析JSON
```c++
//解析json
Json::Reader reader;
Json::Value root2;
//这里为了方便，使用构造的json字符串作为解析json的输入
std::string test_json_string = root.toStyledString();
if (reader.parse(test_json_string, root2, false)) {
  LOGD("解析成功");
  //解析json时，一定要多多检查输入的合法性，避免非法输入造成程序崩溃。
  if (root2.isMember("int")) {
    LOGD("int = %d", root2["int"].asInt());
  }
  if (root2.isMember("str")) {
    LOGD("str = %s", root2["str"].asString().c_str());
  }
  if (root2.isMember("array")) {
    Json::Value obj = root2["array"];
    if (obj.isArray()) {
      for (Json::ArrayIndex i = 0; i < obj.size(); ++i) {
        LOGD("array: %s", obj[i].asString().c_str());
      }
    }
  }
  if (root2.isMember("subJson")) {
    Json::Value sub = root2["subJson"];
    if (sub.isObject()) {
      if (sub.isMember("int")) {
        LOGD("subJson int = %d", sub["int"].asInt());
      }
      if (sub.isMember("str")) {
        LOGD("subJson str = %s", sub["str"].asString().c_str());
      }
    }
  }
}
```