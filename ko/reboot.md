# 시스템 재부팅
다음 코드를 사용하여 시스템을 다시 시작할 수 있습니다.
* 필요한 헤더 파일
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