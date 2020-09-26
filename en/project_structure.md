
# <span id = "project_structure">FlywizOS project code structure introduction</span>
Before you start to write code, you must first understand the basic structure of a FlywizOS project, and then you can know where your code should be added.  
For a basic FlywizOS project, its directory structure is like this :  

![项目结构](assets/project_structure.png)  
It is roughly divided into three folders: **jni**, **resources**, **ui**. The role of each folder is explained below.    

* ## ui  folder  
  Expand **ui** folder   
  
  ![ui文件夹展开](assets/project_ui_expand.png)    
  
  You can see that a **main.ftu** file is included by default. **ftu** is the suffix of the UI file of the **FlywizOS** project. Each **ftu** file corresponds to an application interface. Usually, an application contains multiple interfaces, so you need to create multiple **ftu** files in the **ui** folder. To add a new **ftu** file, please refer to [How to create a new FlywizOS UI file](new_flywizOS_ui_file.md). For the convenience of description, in the following tutorials, the **ftu** file will be referred to as the **UI file**.
  
  You can double-click to open the **UI file**, edit it, and preview the effect instantly. For the specific steps of editing the **UI** file, please refer to the tutorial of **Introduction to Controls**.
  
  After editing, you can start **"compile"** ([How to compile](how_to_compile_flywizOS.md))

  > [!Note]
  > **Note: The compilation mentioned here is not only the compilation of the source code, but also a series of operations such as the preprocessing of the ui file and the generation of the template code, but these are all automated, and you do not need to manually operate. For all the specific operations behind compiling this action, please refer to [The specific compilation process and the correspondence between the UI file and the source code](ftu_and_source_relationships.md#ftu_and_source_relationships). After reading it, I believe you will be easier to understand and get started quickly**
  
* ## resources folder  
  The content of this folder is relatively simple, mainly used to store various resource files of the project, including pictures, fonts, input method configuration files, etc. However, due to the limitation of the machine's own storage space, it is not recommended to store large files in this directory. It is recommended that you store large resource files in the TF card.

We can get the absolute path of a file in the resources directory in the code.
  For example: The following code can obtain the absolute path of resources/test.txt.
 ```c++ 
 #include "manager/ConfigManager.h"
 std::string resPath = CONFIGMANAGER->getResFilePathEx("test.txt");
 ```
* ## jni folder  
   This folder is mainly for storing code files, and it also contains multiple parts of code. We expand the **jni** folder  
   ![](assets/project_jni_expand.png)  
   As you can see, it contains 6 parts of **activity**, **include**, **logic**, **uart**, **Main.cpp**, **Makefile**, each the functions of each part are as follows:
   
   * ### activity subfolder  
     Store the basic class code of the UI file. After each UI file is compiled, an `Activity` class and a `Logic.cc` file with the same prefix name will be generated. For example: there is a **main.ftu** in the ui folder, then after compilation, `mainActivity.h`, `mainActivity.cpp` and `mainLogic.cc` will be generated, and the `mainActivity` class will be stored in ** In the activity** folder, the `mainLogic.cc` file will be stored in the **logic** folder.
     > [!Warning] 
     > **It is strongly recommended not to manually modify the code in the activity folder, except in special cases**
     
   * ### logic subfolder   
    Store specific logic codes. Same as the description above, every UI file will generate a **Logic.cc** file with the corresponding prefix name after compilation. **Note: Our custom code is mainly added to these Logic.cc files* *.
   * ### include subfolder
   The header files related to the system and all control related header files are mainly stored here.
   * ### uart subfolder  
    As the name implies, this folder stores serial port operation related codes, including reading and writing serial ports, protocol analysis, etc.
   * ### Main.cpp
    The entry code of the entire FlywizOS application, including the interface for selecting the boot and some initialization, generally does not need to modify this file.
   * ### Makefile/Android.mk、Application.mk
    Compilation configuration file, which contains the specific source code compilation process, generally does not need to be modified  

After the compilation is passed, the **libs** directory and the **obj** directory will be generated under the project, which are the compiled target storage directory and the compiled intermediate file directory, both of which can be cleaned up or deleted directly. It doesn't matter.

