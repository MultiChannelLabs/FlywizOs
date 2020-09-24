# <span id="new_flythings_project">How to create a new FlywizOS project</span>
Creating a new FlywizOS project is very simple. Specific steps are as follows :
1. In the menu bar at the top of the editor, select **File -> New -> FlywziOS Application Project**  

   ![新建项目](assets/ide/new_flythings_project.gif)  

2. After the selection in the previous step is completed, the **FlywizOS New Wizard** prompt box will pop up. 
  
   ![创建向导第一步](assets/ide/wizard_new_project_page1.png)  
   Fill in the parameters related to the new project as required. These parameters are: 

   * **Project name**  
    The name of the project; it can be a combination of letters and numbers.
   * **Location**  
    The storage path of the project.  
   * **Platform**  
    Choose the corresponding platform according to the serial screen you own, currently there are  
     - **Z11S**  
     - **Z6S**  
   
   After filling in the required parameters as above, you can directly select **Finish** to quickly complete the creation. But for now, we choose **Next** to customize more parameters.
3. After clicking Next, we will see more parameter definitions  
  
   ![新建参数](assets/ide/wizard_new_project_page2.png)  
   
   ## The meaning and function of each attribute of the project :  
   * **Screen saver timeout**  
   
    FlywizOS system provides screensaver function. If there is no touch operation on the serial port screen within the specified time, or you have not reset the screen saver timing through the code, then the system will automatically enter the screen saver.
     If the time is **-1** second, it means that the screen saver function is disabled.
    
   * **Serial port**  
    Specify the communication serial port, and generally do not need to be modified.
     
  * **Baud rate**   
     Specify the baud rate of the communication serial port 
    
   * **Resolution**  
    Specify the width and height of the screen in pixels
     
  * **Screen rotation**  
    For some screen coordinate axis directions, you can check this option to rotate the displayed content by 90° to achieve normal display.
     
  * **Font**  
    FlywizOS supports custom fonts. If you are not satisfied with the default fonts, you can cancel the defaults and select your font file.
    
  * **Input method**  
    If you need Chinese input, you can check it, and cooperate with **[Edit Text box](edittext.md)** control to solve Chinese input.     
  
   The above attributes can be modified again later, so don't worry too much about filling in errors. ([How to modify the attributes of an existing project](set_project_properties.md))  
    After the attributes are filled in and confirmed, click **Finish** to end the creation. The creation process will take some time and wait patiently.  
  
4. After the project is created, you should first understand [FlywizOS project code structure introduction](project_structure#project_structure.md)

