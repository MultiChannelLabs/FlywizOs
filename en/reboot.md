# Restart the system
The following code can be used to actively restart the system machine.
* Required header files
```c++
	#include<unistd.h>
	#include<sys/reboot.h>
```
* Code
```c++
	//Synchronize data and save cached data to prevent data loss
	sync();
	reboot(RB_AUTOBOOT);
```