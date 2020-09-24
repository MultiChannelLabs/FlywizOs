## ADC

> [!Note]
>
> 1. 현재 **SV50P series 모듈**만 ADC를 지원합니다.
> 2. 사용 전, 사용자는 [Module Configuration](https://superv.flythings.cn)에서 ADC기능을 활성화 하고, 이를 위해 시스템 패키지를 업데이트해야 합니다.
> 3. 모듈에 대한 더 자세한 사항은 [Using Tutorial](core_module.md)을 참고하십시오

### 필요 헤더 파일

  ```c++
  #include "utils/AdcHelper.h"
  ```

### 예제

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