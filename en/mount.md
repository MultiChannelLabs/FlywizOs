# TF card plug-in monitor
By registering the monitoring interface, we can know the status of the TF card; here we first need to implement our own monitoring class :

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
Define the listener :
```c++
static MyMountListener sMyMountListener;
```
Register to monitor :
```c++
MOUNTMONITOR->addMountListener(&sMyMountListener);
```
When we no longer need to monitor, we need to un-register the monitor :
```c++
MOUNTMONITOR->removeMountListener(&sMyMountListener);
```
For specific operations, refer to the MountDemo project in [Sample Code](demo_download.md#demo_download)
