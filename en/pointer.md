# Pointer control
## Features
If we want to implement an instrument or clock rotation similar effect, this control can be easily implemented. This control is specially designed to handle graphics rotation.

## Thinking
If we want to implement an pointer, we can disassemble it into two parts, the static background image as the dial and the pointer image that rotates on the background image. 
Therefore, after selecting the background image and the pointer image, we only need to determine the center coordinates of the pointer rotation.

## How to use
1. We first create an **pointer** control, you can see that it has the following properties:  

 ![](assets/pointer/properties.png)  
 If you don’t know how to create a control, you can refer to [How to create a button control](button.md#add_button)   
 In the property picture, you can see that I have added **pointer image** and **background image**
 The adding process is shown in the animation :   

  ![](assets\pointer/add_pointer.gif)

2. Judging from the final preview image above, no problems were found, and the background image and pointer position looked normal. However, after the program actually runs, it is wrong. For quick and easy adjustment, we can set the **starting angle** property to other degrees (default is 0), here we adjust it to 120, we can find that after the pointer is rotated by 120°, the result of the pointer rotation is not what we expect like that.  
 ![](assets/pointer/start_angle_120.png)  
 The reason for this is that the coordinates of the center of the circle where the pointer rotates are incorrect.  
 There are two properties that determine the coordinates of the pointer rotation center, they are **rotation point coordinates** and **fixed point coordinates** 
 * Rotation point coordinates  
    The coordinates are with reference to the entire rectangular area of the control. The upper left corner of the rectangular area of the control is [0,0], in pixels. For such an instrument, obviously the coordinates of the rotation point we want are in the center of the dial. , Then the specific coordinates of the corresponding picture are (250, 250), as shown below :  
   ![](https://box.kancloud.cn/940c7a9a077fdf8442ff4969a8e523c1_260x204.png)  
* Fixed point coordinates  
 The coordinates refer to the pointer picture, the upper left corner of the picture is [0,0], and the unit is pixel. For such a pointer picture, the fixed point coordinates of the pointer we want is (30, 210)  
 ![](https://box.kancloud.cn/05171e54018b720825d8e84c785f9aa5_80x146.png)  

After filling the two coordinates into the attribute table, you can see that the pointer rotates to the correct position  

![](assets/pointer/preview2.png)

**Starting angle** supports negative numbers. In the above example, if **change the starting angle** to -120, the pointer just points to the dial 0 position.

## Tips on the fixed point of the pointer  
 In the above example, the coordinate of the fixed point of the pointer is located in the pointer picture. In fact, this coordinate can also exceed the range of the picture to achieve the effect of the cursor. As shown in the figure below, the white in the red box is actually a pointer picture, which is relatively small, but in the property on the right, I set the coordinates of the fixed point of the pointer far beyond the real size of the picture, and then adjust the rotation coordinates to implement the effect of the circular cursor.

 ![](assets/pointer/preview3.png)

## Operation method 
The most common method for this type of control is to adjust the rotation angle of the pointer through code. 
```c++
//Adjust the pointer to 90 degrees
mPointer1Ptr->setTargetAngle(90.0);
```


# Sample code
For the use of specific pointer controls, refer to the PointerDemo project in [Sample Code](demo_download.md#demo_download).