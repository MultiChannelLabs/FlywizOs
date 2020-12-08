## ADC

> [!Note]
>
> 1. 現在**SV50P seriesモジュール**のみADCをサポートします。
> 2. 使用前に、ユーザーは[Module Configuration](https://www.flywizos.com)でADC機能を有効にして、そのためにシステムのパッケージを更新する必要があります。
> 3. モジュールの詳細については、[Using Tutorial](core_module.md)を参照してください。

### 必要ヘッダファイル

  ```c++
  #include "utils/AdcHelper.h"
  ```

### 例

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