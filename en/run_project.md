# How to run the project
  After the project passes [compile](how_to_compile_flythings.md), it can be put to run on the real machine. According to different equipment models, there are several operating modes as follows:

## Use WIFI to connect devices quickly
  This method **only supports models with WIFI**, and the currently supported device models are: 

 * sw480272043B_CW  4.3inch
 * sw480272043B_CWM 4.3inch
 * sw80480043B_CW  4.3inch
 * sw48854050B_CW   5inch
 * sw80480070A_CW   7inch
 * sw80480070A_CWM  7inch
 * sw80480070AI_CW     7inch
 * sw80480070AI_CWM    7inch
 * sw10600070A_CW   7inch

 > [Product model description](board_tag_explain.md)

After confirming that the device supports WIFI, follow the steps below to complete the configuration:
1. First enter the [WIFI setting activity](wifi.md) of the device, and connect the device to the same wireless network as the computer, that is, the computer and the machine must be connected to the same WIFI. (If a different network will cause the subsequent download procedure to fail).
2. After the wireless network connection is successful, click the menu in the upper right corner of the WIFI setting activity to check the IP address of the device.  
3. At this time, go back to the development tool on the computer, on the menu bar, select the menu **FlywizOS** -> **ADB Configuration**, in the pop-up box, select **Net** for the ADB connection method, and Fill in the IP address of the device and save the application.
4. After completing the connection configuration, select the [Download and Debug](adb_debug.md) menu item, it will temporarily synchronize the project code to the connected device to run.

## Fast operation with USB connected device
For models without WIFI function, almost all support USB cable connection. **Note: If there is WIFI function, the USB cable connection is invalid.**

1. Connect the device to the computer via a USB cable. If the computer can recognize the device as an Android device, the connection is normal. If you can't connect normally, the computer prompts a driver problem, you can try [Download Driver](install_adb_driver.md).
2. When the computer recognizes the device correctly, return to the development tool on the computer, in the menu bar, select the menu **FlywizOS** -> **ADB Configuration**, in the pop-up box, select the ADB connection method **USB** and save.
3. After the configuration is complete, select the [Download and Debug](adb_debug.md) menu item, it will temporarily synchronize the project code to the connected device to run.


## Boot from TF card
If for other reasons, both USB and WIFI cannot be used normally or are occupied, you can start the program from the TF card with the help of a TF card.
For specific steps, please refer to [Start the program from the TF card](start_from_sdcard.md)