# Make update image file
In the previous tutorial, we used the [Download and Debug](adb_debug.md#下载调试) menu to run the program, but **it cannot write the program into the device. If you unplug the TF card or power off and restart, the program will automatically recover**. If you want the **writing program** to be in the device, we can package the program into an update file. After the device is updated, the program can be written inside the device. Once the power is turned on, the program will be started by default.

## Specific steps  
First we need to configure the output directory of the mirror.
1. Find this button on the toolbar

   ![](assets/ide/toolbar_image.png)   

2. Click the black drop-down arrow next to it, and select **Path Setup** in the pop-up menu

   ![](assets/ide/toolbar_image23.png)

3. In the pop-up box, select the output directory of the image file, and click OK.

4. In the above steps, we have configured the output directory. Now click the button in the figure below to start compiling. It will package the compilation result and generate the **update.img** file and output it to the configured directory.  

     ![](assets/ide/toolbar_image3.png)

5. After the **update.img** file is successfully generated, copy it to the TF card (**Note: Before using, please format the TF card in FAT32 format**), and insert the TF card into the machine. At this time, the system detects the files in the TF card and will start the update program. In the activity shown in the figure below, check the update items and click update button. After the update is completed, remove the update card in time to prevent repeated update.
  > [!NOTE]
  > **Note: TF card only supports FAT32 format**

   ![](images/screenshot_1513263522327.png)

**If the screen is damaged or the touch is inaccurate, which makes it impossible to update by clicking the button, then in this case, we can use [Auto Update](autoupgrade.md) this way update our system. **