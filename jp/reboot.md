# システムの再起動
次のコードを使用してシステムを再起動することができます。
* 必要なヘッダファイル
```c++
	#include<unistd.h>
	#include<sys/reboot.h>
```
* 코드
```c++
	//Synchronize data and save cached data to prevent data loss
	sync();
	reboot(RB_AUTOBOOT);
```