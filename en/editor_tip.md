# Common settings for development tools

## <span id = "jump_to_source"> Quick jump to related functions</span>
When we add too many controls to the UI file, multiple associated functions will also be generated in the **Logic.cc** file. If you want to find the associated function of a certain control is quite time-consuming.  
Fortunately, the tool provides a function to quickly jump from the UI control to the relevant code.  
On the preview, select a control, right-click, and select **Goto relative code** in the pop-up menu to open the corresponding Logic.cc file, and position the cursor to the associated function of the control.  

   ![](assets/ide/jump_to_source.png)

> **Note: This function is only valid for control types that automatically generate associated functions, such as the control types mentioned above. If you choose other control types, the function will only jump to the corresponding Logic.cc file , And position the cursor at the bottom of the file. **


---

## Modify font/font size 
1. On the menu bar of the tool, select **Window** -> **Preferences** 

      ![](assets/ide/preference.png)

2.  In the pop-up box, select according to the following figure in turn to set the font.    
  
     ![](assets/ide/set_font.png)

## Code smart completion  
When editing the code, you first need to input the starting part, and then press "**Alt + /**" to turn on the code completion function.  
As shown in the figure below, I input the two letters **UA**, and then press "**Alt + /**" shortcut key, you can see that there are multiple completion options, which can be selected with the up and down arrow keys. **Enter** key confirms the selection.

  ![](assets/ide/intelisence.png)


## Reindex
 If the code completion function fails, or the editor prompts a code error, but there is no problem with the compilation, please try to rebuild the index. 

 The steps to rebuild the index are as follows :

 ![](assets/ide/rebuild_index.gif)  
