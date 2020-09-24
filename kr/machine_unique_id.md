# Device unique ID code

## How to read
* Required header file
 ```c++
 #include "security/SecurityManager.h"
 ```
* Read device ID
    ```c++
    // Device id 8 bytes
    unsigned char devID[8];
    // Return true on success, false on failure
    bool ret = SECURITYMANAGER->getDevID(devID);
    ```