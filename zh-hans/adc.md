## ADC操作

> [!Note]
> 1. 目前仅**SV50P系列模组**支持该功能。
> 2. 使用前，需要在[模组配置](https://superv.flythings.cn)中使能 **ADC** 功能，用生成的新系统包升级，才能正常使用。
> 3. 更多有关模组的[使用教程](core_module.md)。

### 引入头文件

  ```c++
  #include "utils/AdcHelper.h"
  ```

### 具体操作

  ```c++
  #include "utils/AdcHelper.h"

  static void testAdc() {
	/**
	 * 设置adc使能状态
	 *
	 * @param true 使能
	 *        false 禁止   
	 *         默认是使能状态
	 */
	AdcHelper::setEnable(true);

	for (int i = 0; i < 10; i++) {
	  // 读取adc值
	  int val = AdcHelper::getVal();
	  LOGD("adc val = %d\n", val);
	}
  }
  ```