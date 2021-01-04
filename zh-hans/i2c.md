## I2C操作

> [!Note]
> 1. 目前仅**SV50P系列模组**支持该功能。
> 2. 使用前，需要在[模组配置](https://superv.flythings.cn)中使能 **TWI** 功能，用生成的新系统包升级，才能正常使用。
> 3. 更多有关模组的[使用教程](core_module.md)。

### 引入头文件

  ```c++
  #include "utils/I2CHelper.h"
  ```

### 具体操作

  ```c++
  #include "utils/I2CHelper.h"

  #define CFG_L		0x47
  #define CFG_H		0x80
  #define VER_L		0x41
  #define VER_H		0x81

  static void testI2C() {
	uint8_t tx[512], rx[512];
	memset(tx, 0, 512);
	memset(rx, 0, 512);

	/**
	 * 定义变量
	 *
	 * 参数1： i2c总线号
	 * 参数2： 从机地址, 一定要注意是 7bit地址
	 * 参数3： 超时时间，单位: ms
	 * 参数4： 重试次数
	 */
	I2CHelper i2c(0, 0x5e, 1000, 5);

	tx[0] = CFG_H;
	tx[1] = CFG_L;

	/**
	 * 单工写
	 *
	 * 参数1： 写数据地址
	 * 参数2： 数据长度
	 */
	if (!i2c.write(tx, 2)) {
		LOGD("i2c tx cfg error!\n");
	}

	/**
	 * 单工读
	 *
	 * 参数1： 读数据地址
	 * 参数2： 数据长度
	 */
	if (!i2c.read(rx, 1)) {
		LOGD("i2c rx cfg error!\n");
	}

	LOGD("i2c reg[0x%x%x]=%x\n", CFG_H, CFG_L, rx[0]);
	memset(rx, 0, 512);

	/**
	 * 半双工传输，即共用读写，中间无stop信号
	 *
	 * 参数1： 写数据地址
	 * 参数2： 写数据长度
	 * 参数3： 读数据地址
	 * 参数4： 读数据长度
	 */
	if (!i2c.transfer(tx, 2, rx, 1)) {
		LOGD("i2c i2c_transfer cfg error!\n");
	}

	LOGD("i2c reg[0x%x%x]=%x\n", CFG_H, CFG_L, rx[0]);

	tx[0] = VER_H;
	tx[1] = VER_L;
	if (!i2c.write(tx, 2)) {
		LOGD("i2c tx ver error!\n");
	}

	if (!i2c.read(rx, 1)) {
		LOGD("i2c rx ver error!\n");
	}

	LOGD("i2c reg[0x%x%x]=%x\n", VER_H, VER_L, rx[0]);
	memset(rx, 0, 512);
	if (!i2c.transfer(tx, 2, rx, 1)) {
		LOGD("twi i2c_transfer ver error!\n");
	}

	LOGD("i2c reg[0x%x%x]=%x\n", VER_H, VER_L, rx[0]);
  }
  ```

其他接口操作请参见头文件注释说明。
