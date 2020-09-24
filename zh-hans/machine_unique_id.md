# 设备唯一ID码

## 如何读取
* 所需头文件
 ```c++
 #include "security/SecurityManager.h"
 ```
* 读取设备ID
    ```c++
    // 设备 id 共8个字节
    unsigned char devID[8];
    // 成功返回 true，失败返回 false
    bool ret = SECURITYMANAGER->getDevID(devID);
    ```