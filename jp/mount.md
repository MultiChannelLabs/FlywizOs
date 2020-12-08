# TF card plug-in monitor
 TFカードの監視機能を登録することでTFカードの状態を知ることができます。以下は実装のための最初の必要です。

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
Listener 定義 :
```c++
static MyMountListener sMyMountListener;
```
登録 :
```c++
MOUNTMONITOR->addMountListener(&sMyMountListener);
```
登録解除 :
```c++
MOUNTMONITOR->removeMountListener(&sMyMountListener);
```
詳細は、[サンプルコード](demo_download.md＃demo_download)のMountDemoプロジェクトを参照してください。
