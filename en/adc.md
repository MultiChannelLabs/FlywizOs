## ADC operation(操作)

> [!Note]
> 1. Currently only **SV50P series modules** support this function.(目前仅**SV50P系列模组**支持该功能。)
> 2. Before use, you need to enable the **ADC** function in [Module Configuration](https://superv.flythings.cn) and upgrade with the generated new system package before it can be used normally.(使用前，需要在[模组配置](https://superv.flythings.cn)中使能 **ADC** 功能，用生成的新系统包升级，才能正常使用。)
> 3. More about the module [Using Tutorial](core_module.md).(更多有关模组的[使用教程](core_module.md)。)

### 引入头文件

  ```c++
  #include "utils/AdcHelper.h"
  ```

### 具体操作

  ```c++
  #include "utils/AdcHelper.h"

  static void testAdc() {
	/**
	 * Set the adc enable state(设置adc使能状态)
	 *
	 * @param true enable(使能)
	 *        false disable(禁止)
	 *         The default is enable(默认是使能状态)
	 */
	AdcHelper::setEnable(true);

	for (int i = 0; i < 10; i++) {
	  // read adc value(读取adc值)
	  int val = AdcHelper::getVal();
	  LOGD("adc val = %d\n", val);
	}
  }
  ```