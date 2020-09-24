

# Window control

## Function description
The window is actually a container part. It can contain all the controls, or it can contain a new window again. Can be used in the following scenarios
* Show and hide a control combination
* When you need to complete the tab page, you can switch between different windows through multiple windows
* Pop-up dialog
* Pop up floating box

## How to use  
1. Create a **Window** control, the default window is transparent. You can add a background image or modify the background color according to your needs; you can also add other controls to the window.  

   ![](assets/window/properties.png)
2. In the above attribute table, there are two attributes that need to be explained : 
  * **Modal**  
    If it is modal, when this window control is displayed, click outside the window, the window will be automatically hidden.  
    If it is non-modal, the display/hide of the window control must be controlled by itself.
  * **Timeout auto hide**  
    If it is a modal window, the window will start counting from the beginning of the display and will be automatically hidden after the **Timeout auto hide** time. The unit is seconds; if the value is -1, it means that it will not be hidden automatically.  
    If it is non-modal, then this parameter has no effect.

## Operation code
For window controls, we generally involve the following functions
```C++
//Show window
void showWnd();
//Hide window
void hideWnd();
//Determine whether the window is displayed
bool isWndShow();
```

## Dynamically set background
If we spread the window all over the screen and then set the background of this window, we can achieve the effect of modifying the screen background.

* Related function
  ```c++
	/**
	 * @brief Set background picture
	 * @param pPicPath Picture path
	 */
	void setBackgroundPic(const char *pPicPath);

	/**
	 * @brief Set background color
	 * @param color When -1, the background is set to transparent; other color values are 0xRGB, and the color value does not 
	 * support alpha
	 */
  void setBackgroundColor(int color);
  ```
  
* Usage example
  ```c++
	//Set the image of the path /mnt/extsd/bg.png as the background image of this window control
	mWindow1Ptr->setBackgroundPic("/mnt/extsd/bg.png");
	
	//Set the background color of the window with ID window1 to red
	mWindow1Ptr->setBackgroundColor(0xff0000);
    
  //Set the background color of the window with ID window1 to green
	mWindow1Ptr->setBackgroundColor(0x00ff00);
        
  //Set the background color of the window with ID window1 to blue
	mWindow1Ptr->setBackgroundColor(0x0000ff);
	```

  Many controls have functions for setting the background color and background image, and the methods are the same.

# Sample code
Demonstrates the use of modal/non-modal window controls  

![](assets/window/preview.png) 

For specific use of window controls, refer to the WindowDemo project in [Sample Code](demo_download.md#demo_download)