## I2C operating

> [!Note]
> 1. Currently only **SV50P series modules** support this function.
> 2. Before use, you need to enable the **TWI** function in [Module Configuration](https://superv.flythings.cn) and upgrade with the generated new system package before it can be used normally.
> 3. More about the module [Using Tutorial](core_module.md).

### Required header file

  ```c++
  #include "utils/I2CHelper.h"
  ```

### Specific operation

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
	 * Define variables
	 *
	 * Parameter 1: i2c bus number
	 * Parameter 2: Slave address, be sure to pay attention to the 7bit address
	 * Parameter 3: Timeout time, unit: ms
	 * Parameter 4: Number of retries
	 */
	I2CHelper i2c(0, 0x5e, 1000, 5);

	tx[0] = CFG_H;
	tx[1] = CFG_L;

	/**
	 * Simple write
	 *
	 * Parameter 1: Write data address
	 * Parameter 2: Data length
	 */
	if (!i2c.write(tx, 2)) {
		LOGD("i2c tx cfg error!\n");
	}

	/**
	 * Simple read
	 *
	 * Parameter 1: Read data address
	 * Parameter 2: Data length
	 */
	if (!i2c.read(rx, 1)) {
		LOGD("i2c rx cfg error!\n");
	}

	LOGD("i2c reg[0x%x%x]=%x\n", CFG_H, CFG_L, rx[0]);
	memset(rx, 0, 512);

	/**
	 * Half-duplex transmission, that is, shared read and write, no stop signal in the middle
	 *
	 * Parameter 1: Write data address
	 * Parameter 2: Write data length
	 * Parameter 3: Read data address
	 * Parameter 4: Read data length
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

For other interface operations, please refer to the header file notes.
