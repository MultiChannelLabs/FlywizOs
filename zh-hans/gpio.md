## GPIO操作

> [!Note]
> 1. 如果是购买的**SV50PB模组**或者**SV50PC模组**，使用前，需要在[模组配置](https://superv.flythings.cn)中使能 **GPIO** 功能，再重新升级系统,才能正常使用。
> 3. 更多有关模组的[使用教程](core_module.md)。

### 引入头文件
```c++
#include "utils/GpioHelper.h"
```


### 操作函数
```c++
class GpioHelper {
public:
    /**
	 * 将脚位设置为输入模式，并返回脚位的高低状态
	 * @param pPin 脚位名
	 * @return  -1 操作失败 
	 *           1 高电平
	 *           0 低电平
	 */
	static int input(const char *pPin);
	/**
	 * 将脚位设置为输出模式, 并指定输出高电平或者低电平
	 * @param pPin 脚位名
	 * @param val 1 高电平
	 *            0 低电平
	 * @return   -1 失败
	 *            0 成功
	 */
	static int output(const char *pPin, int val);
};
```


### 各个平台可操作脚位名称定义

  * Z11S平台

    目前该平台只保留了3组io口可以操作。
  
  ```c++
    // 3组io口定义
    #define GPIO_PIN_B_02		"B_02"
    #define GPIO_PIN_B_03		"B_03"
    #define GPIO_PIN_E_20		"E_20"
        
    #include "utils/GpioHelper.h"

    // 读B02 io口状态
    GpioHelper::input(GPIO_PIN_B_02);

    // B02 io口输出高电平
    GpioHelper::output(GPIO_PIN_B_02, 1);
  ```

  * SV50PB模组

    有以下12组io口可以操作：

  ```c++
    // SV50PB
    #define SV50PB_PIN7         "PIN7"
    #define SV50PB_PIN8         "PIN8"
    #define SV50PB_PIN9         "PIN9"
    #define SV50PB_PIN10        "PIN10"
    #define SV50PB_PIN11        "PIN11"
    #define SV50PB_PIN12        "PIN12"
    #define SV50PB_PIN13        "PIN13"
    #define SV50PB_PIN14        "PIN14"
    #define SV50PB_PIN23        "PIN23"
    #define SV50PB_PIN24        "PIN24"
    #define SV50PB_PIN26        "PIN26"
    #define SV50PB_PIN27        "PIN27"

    #include "utils/GpioHelper.h"

    // 读PIN7 io口状态
    GpioHelper::input(SV50PB_PIN7);

    // PIN7 io口输出高电平
    GpioHelper::output(SV50PB_PIN7, 1);
  ```

  * SV50PC模组

    有以下25组io口可以操作：

 ```c++
    // SV50PC
    #define SV50PC_PIN2         "PIN2"
    #define SV50PC_PIN3         "PIN3"
    #define SV50PC_PIN4         "PIN4"
    #define SV50PC_PIN5         "PIN5"
    #define SV50PC_PIN6         "PIN6"
    #define SV50PC_PIN7         "PIN7"
    #define SV50PC_PIN8         "PIN8"
    #define SV50PC_PIN9         "PIN9"
    #define SV50PC_PIN10        "PIN10"
    #define SV50PC_PIN11        "PIN11"
    #define SV50PC_PIN13        "PIN13"
    #define SV50PC_PIN14        "PIN14"
    #define SV50PC_PIN15        "PIN15"
    #define SV50PC_PIN16        "PIN16"
    #define SV50PC_PIN17        "PIN17"
    #define SV50PC_PIN18        "PIN18"
    #define SV50PC_PIN22        "PIN22"
    #define SV50PC_PIN24        "PIN24"
    #define SV50PC_PIN25        "PIN25"
    #define SV50PC_PIN26        "PIN26"
    #define SV50PC_PIN27        "PIN27"
    #define SV50PC_PIN28        "PIN28"
    #define SV50PC_PIN29        "PIN29"
    #define SV50PC_PIN30        "PIN30"
    #define SV50PC_PIN31        "PIN31"

    #include "utils/GpioHelper.h"

    // 读PIN7 io口状态
    GpioHelper::input(SV50PC_PIN7);

    // PIN7 io口输出高电平
    GpioHelper::output(SV50PC_PIN7, 1);
 ```
 
  * 86盒子

    有以下4组io口可以操作：

 ```c++
    // 86 Box
    #define Z6X86BOX_PIN7         "PIN7"	// 对应硬件上IO1
    #define Z6X86BOX_PIN8         "PIN8"	// IO2
    #define Z6X86BOX_PIN9         "PIN9"	// IO3
    #define Z6X86BOX_PIN10        "PIN10"	// IO4

    #include "utils/GpioHelper.h"

    // 读PIN7 io口状态
    GpioHelper::input(Z6X86BOX_PIN7);

    // PIN7 io口输出高电平
    GpioHelper::output(Z6X86BOX_PIN7, 1);
 ```

### 样例  
完整源码见[**样例代码包**](demo_download.md#demo_download)中的**GpioDemo**项目
