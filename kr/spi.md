## SPI操作

> [!Note]
> 1. 目前仅**SV50PB模组**支持该功能。
> 2. 使用前，需要在[模组配置](https://superv.flythings.cn)中使能 **SPI** 功能，用生成的新系统包升级，才能正常使用。
> 3. 更多有关模组的[使用教程](core_module.md)。

### 引入头文件

  ```c++
  #include "utils/SpiHelper.h"
  ```

### 具体操作

  ```c++
  // 所需头文件
  #include "utils/SpiHelper.h"

  static void testSpi() {
	uint8_t tx[512], rx[512];

	/**
	 * 定义变量
	 *
	 * 参数1： spi总线号
	 * 参数2： 模式，可选值： SPI_MODE_0、SPI_MODE_1、SPI_MODE_2、SPI_MODE_3
	 * 参数3： spi时钟频率，这里设置了50M
	 * 参数4： 一个字有多少位，默认值： 8
	 * 参数5： 位顺序，true： 表示低位在前，false： 表示高位在前； 默认值： false，高位在前
	 */
	SpiHelper spi(1, SPI_MODE_0, 50*1000*1000, 8, false);

	memset(tx, 0, 512);
	memset(rx, 0, 512);

	tx[0] = 0x4B;

	/**
	 * 单工写
	 *
	 * 参数1： 写数据地址
	 * 参数2： 数据长度
	 */
	if (!spi.write(tx, 5)) {
		LOGD("spi tx error!\n");
	}

	/**
	 * 单工读
	 *
	 * 参数1： 读数据地址
	 * 参数2： 数据长度
	 */
	if (!spi.read(rx, 8)) {
		LOGD("spi rx error!\n");
	}

	for (int i = 0; i < 8; i++) {
		LOGD("spi[%d]=0x%x\n", i, rx[i]);
	}

	/**
	 * 半双工传输
	 *
	 * 参数1： 写数据地址
	 * 参数2： 写数据长度
	 * 参数3： 读数据地址
	 * 参数4： 读数据长度
	 */
	if (!spi.halfduplexTransfer(tx, 5, rx, 8)) {
		LOGD("spi spi_halfduplex_transfer rx error!\n");
	}

	for (int i = 0; i < 8; i++) {
		LOGD("spi[%d]=0x%x\n", i, rx[i]);
	}
  }
  ```

其他接口操作请参见头文件注释说明。
