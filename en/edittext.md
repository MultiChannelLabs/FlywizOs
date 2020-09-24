# Edit Text
## I need a numeric keyboard, and I need the user to manually input Text, what should I do?
[How to add edit/input box](#add_edit_text)

## <span id = "add_edit_text">How to add Edit Text box</span>
If you need numeric and text input, you can quickly implement it by using the existing `Edit Text` controls. The specific steps are as follows:
1. Double click to open the main.ftu file

2. Find the `Edit Text` control in the right control collection

3. Left-click the `Edit Text` control and hold it, then drag it to any position, release the left button, you can see the control of the automatic edit/input box.

4. In the properties on the right, select **Input Type** according to your needs. If you need to enter text, then select **Text**.

5. When the download is running on the machine, click on the `Edit Text` control, and a built-in input method or numeric keyboard of the system will automatically open, so that you can enter text or numbers.

    ![创建编辑框](assets/EditText-create.gif)     

    Built-in text input method screenshot
     ![](assets/edittext/input_method.jpg)    

    

    

    Built-in numeric keyboard input screenshot
      ![](assets/edittext/input_method_num.jpg)

The default `Edit Text` is white, you can customize the appearance style in the property table on the right. Among them, the relevant properties of the `Edit Text` are as follows:
  * **Password**  
    If you choose Yes, when you simulate keyboard input, the character you are typing will be displayed as the specified `password character`, otherwise no change
  * **Password Char**  
    If you select `Yes for Password`, the character you are typing will be displayed as the specified `Password Char`, otherwise no change
  * **Input Type**  
    There are two options for this property, respectively are 
       * Text  
        Means that you can enter English and numbers without restriction.
       * Number  
        Indicates that only numbers can be input, others are restricted.
  * **Hint Text**  
    When the content in the simulated keyboard is empty, the prompt text will be displayed automatically.
  * **Hint Text Color**  
    When the content in the simulated keyboard is empty, the prompt text will be displayed automatically, and the text color is the specified color.

## How to get the input content of the simulated keyboard?
When the `Edit Text` is successfully created, select **compile FlywizOS**, and its associated function will be automatically generated,

Open the `jni/logic/****Logic.cc` file (\*\*\*\* represents the UI file name) in the project directory, and find the automatically generated function    
(`XXXX` represents the control ID name) [Learn more about the relation function of the control](relation_function.md)

```c++
static void onEditTextChanged_XXXX(const std::string &text) {
	  //LOGD("The current input is %s \n", text.c_str());
}
```
When the simulated keyboard input is finished, the system will automatically call this function, and the parameter `text` is the complete string on the current simulated keyboard.  
`std::string` is a string of C++ language. You can also get the string pointer in C language through the following statement.

```
const char* str = text.c_str();
```



## How to convert a string to a number? 
In the associated function of the `Edit Text`, we can only get the string, so when we input the number, we need to convert the number string to the number.
* The `atoi` function can convert a string to a corresponding number, for example, "213" can be converted to an integer `213`  
  If illegal characters are encountered, the conversion will fail or the parsing will be interrupted. E.g:  
  `atoi("213abc");` return `213`  
  `atoi("abc");`  return `0`
```
static void onEditTextChanged_EditText1(const std::string &text) {
  int number = atoi(text.c_str());
  LOGD("String to number = %d", number);
}
```
* The `atof` function can convert a string to a corresponding floating point number, for example, "3.14" can be converted to a floating point number `3.14`  
  If illegal characters are encountered, the conversion will fail or the parsing will be interrupted. E.g :  
  `atoi("3.14abc");` return `3.14`  
  `atoi("abc");`  return `0`
```C++
static void onEditTextChanged_EditText1(const std::string &text) {
  // The atof function can convert a string to a corresponding floating point number, for example, "3.14" can be converted to an   // integer 3.14
  // If the parameters are not standardized, the conversion will fail, and the number 0 will be returned uniformly
  double f = atof(text.c_str());
  LOGD("Convert string to floating point = %f", f);
}
```

## How to customize the input method?
In addition to using the default input method, we can also customize the input method. [**Sample Code Package**](demo_download.md#demo_download) provides a demonstration example **ImeDemo** project.   
Currently only supports the customization of numbers and letters input.

There are some differences between the implementation of the input method interface and the ordinary interface :
1. The normal interface is implemented by inheriting `Activity`, and the input method needs to inherit `IMEBaseApp` ;
2. In addition, the registration method is different. The normal interface registration method: `REGISTER_ACTIVITY(****Activity);`, the input method interface registration method: `REGISTER_SYSAPP(APP_TYPE_SYS_IME, ****Activity);`(\*\*\ *\* indicates the UI file name)

These differences have been modified in the **ImeDemo** project, just migrate to your own project :
1. Copy the `UserIme.ftu` file in the ui directory to the ui directory of your own project.
2. Copy the files `UserImeActivity.h` and `UserImeActivity.cpp` in the activity directory to the activity directory of your own project.
3. Copy the `UserImeLogic.cc` file in the logic directory to the logic directory of your project.

The subsequent operation is consistent with the normal interface programming, and the logic is written in `UserImeLogic.cc`.