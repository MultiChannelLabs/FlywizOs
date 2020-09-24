# TF card

When the TF card is inserted, the system will automatically mount as the `/mnt/extsd` directory.  

### File path 
If there is a `test.txt` file in the root directory of your TF card, then on our machine, the absolute path of this file is `/mnt/extsd/test.txt`.  


## Notes for writing TF card
 To write files to the TF card, try to follow the following operation sequence, otherwise it may cause the situation that it cannot be written.  
`Insert card`->`Power on`->`Open file`->`Read and write files`->`fflush()`->`Close file`->`sync()`->`Unplug card` 
 In other words, if there is a need to write to a TF card, try to ensure that the TF card has been inserted before turning on the machine, rather than temporarily inserting the TF card when it is turned on.  
 And after writing, pay attention to synchronization issues.

## Determine whether to mount the TF card
```c++
#include "os/MountMonitor.h"
```
```c++
  if (MOUNTMONITOR->isMount()) {
    //TF card has been mounted
  } else {
    //TF card is not mounted
  }
```


> [!Note]
> The `/mnt/extsd` directory always exists, regardless of whether the TF card is inserted  
> Without the TF card inserted, if you read and write the directory, the content will be saved in the memory, but it will disappear if the power is off.
