# JSON 구성과 해석
기본적으로 프로젝트에는 오픈 소스 `cppjson` library가 포함되어 있어 바로 사용이 가능합니다.

## 사용 방법
### 필요한 헤더 파일
```c++
#include "json/json.h"
```

### JSON string 구성
```c++
Json::Value root;
//Add integer value
root["int"] = 1;
//Add string
root["str"] = "hello";

//Due to the accuracy printing problem of floating-point numbers, it is not recommended to use, try to convert to integer
root["float"] = 3.14f;

//add array
Json::Value array;
array.append("123");
array.append("456");
array.append("789");
root["array"] = array;

//json nesting
Json::Value sub;
sub["int"] = 1;
sub["str"] = "sub str value";
root["subJson"] = sub;

LOGD("The generated json string is : ");
LOGD("%s", root.toStyledString().c_str());
```

### ParsingJSON
```c++
//Parsing json
Json::Reader reader;
Json::Value root2;
//For convenience, Use the constructed json string as input for parsing json
std::string test_json_string = root.toStyledString();
if (reader.parse(test_json_string, root2, false)) {
  LOGD("Parsed successfully");
  //When parsing json, you must check the legitimacy of the input more to avoid the program crash caused by illegal input.
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