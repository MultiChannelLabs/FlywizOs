# Digital clock
The digital clock is a control dedicated to time display. In many scenarios, we need to display the time. This control will automatically display according to the system time.
## How to use
1. Double click to open the UI file
2. Find the `digital clock` control in the control set on the right
3. Left-click the `digital clock` control and hold it, then drag it to any position, release the left button, and you can see the digital clock control.
4. Select the digital clock control just generated, in the property bar on the right side of the editor, you can modify its property content, mainly modify the following five properties.

	![](assets/clock/clock1.png)
	
  * Format
	This property sets the display format of the time, you can choose a 24-hour system or a 12-hour system, and control whether the seconds are displayed.
  * Blinking
	This property controls whether the `:` in the clock is static or beating.
  * Color
	This property sets the color display of the clock text.
  * Font size
	The text size of the digital clock
  * Picture Character Set  
	We know that, according to the definition of ascii code, there is a correspondence between `character char` and `integer int`. For example, the ascii code of the character `0` is `48`. The special character set is a function of mapping the ascii code to the picture. After setting this function, when we display a string, the system will try to map each character in the string to a specified picture, and finally display a string of pictures on the screen.  For specific usage, please refer to [Use of Special Character Set](textview.md) in the text control  
5. Save, download and debug, after running, you can see the effect. 
6. If you want to modify the time, you can refer to the [System Time](system_time.md) document to modify.


# Sample code 

![](assets/clock/example.png) 

Refer to the DigitalClockDemo project in [Sample Code](demo_download.md#demo_download)