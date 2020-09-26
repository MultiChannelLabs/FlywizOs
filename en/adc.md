## ADC operation

> [!Note]
>
> 1. Currently only **SV50P series modules** support this function.
> 2. Before use, you need to enable the **ADC** function in [Module Configuration](https://superv.flythings.cn) and upgrade with the generated new system package before it can be used normally.
> 3. More about the module [Using Tutorial](core_module.md).

### Required header file

  ```c++
  #include "utils/AdcHelper.h"
  ```

### Operation

  ```c++
  #include "utils/AdcHelper.h"

  static void testAdc() {
	/**
	 * Set the adc enable state
	 *
	 * @param true enable
	 *        false disable
	 *         The default is enable
	 */
	AdcHelper::setEnable(true);

	for (int i = 0; i < 10; i++) {
	  // read adc value
	  int val = AdcHelper::getVal();
	  LOGD("adc val = %d\n", val);
	}
  }
  ```