# TF card plug-in monitor
 TF 카드 모니터링 함수를 등록하는 것으로 TF카드의 상태를 알 수 있습니다. 아래는 구현을 위해 가장 먼저 필요한 것입니다.

```c++
#include "os/MountMonitor.h"

class MyMountListener : public MountMonitor::IMountListener {
public:
	virtual void notify(int what, int status, const char *msg) {
		switch (status) {
		case MountMonitor::E_MOUNT_STATUS_MOUNTED:	// insert
			// msg is the mount path
			LOGD("mount path: %s\n", msg);
			mMountTextviewPtr->setText("TF inserted");
			break;

		case MountMonitor::E_MOUNT_STATUS_REMOVE:	// remove
			// msg is the unmount path
			LOGD("remove path: %s\n", msg);
			mMountTextviewPtr->setText("TF removed");
			break;
		}
	}
};
```
Listener 정의 :
```c++
static MyMountListener sMyMountListener;
```
등록 :
```c++
MOUNTMONITOR->addMountListener(&sMyMountListener);
```
등록 해제 :
```c++
MOUNTMONITOR->removeMountListener(&sMyMountListener);
```
더 자세한 사항은 [예제 코드](demo_download.md#demo_download)의 MountDemo 프로젝트를 참고하십시오.
