
# 通讯案例实战

通过前面章节[通讯框架讲解](serial_framework.md)，可能看的也是云里雾里的，这里我们先总结一下，串口通讯主要有以下4点内容：
1. 接收数据
2. 解析数据
3. 展示数据
4. 发送数据

其中 **解析数据** 部分较为复杂，需要根据具体的通讯协议做相应的改动；这一章节我们就不讲理论的东西了，举一些实战案例，大伙多玩几遍就可以玩溜了。

## 案例一 

这里我们还是以前面的通讯协议为例，实现自己的一个简单的通讯程序；  
完整代码见 [样例代码](demo_download.md#demo_download) 里控件样例的 `UartDemo` 工程；  
我们最终要实现的效果是，通过串口发送指令来控制显示屏上的仪表指针旋转，UI效果图如下：

   ![](https://ae01.alicdn.com/kf/HTB1JhMbaULrK1Rjy0Fj762YXFXa5.png)

我们只需要修改 **3处** 地方就可以实现控制仪表指针旋转；

**1).** 重温一下前面介绍的协议格式，这里我们新增自己的协议指令**CMDID_ANGLE**对应的值为**0x0001**：

| 协议头（2字节） | 命令（2字节） | 数据长度（1字节） | 数据（N） | 校验（1字节 可选) |
| --- | --- | --- | --- | --- |
| 0xFF55 | 0x0001（见以下`CMDID_ANGLE`） | 1 | angle | checksum |

协议数据结构体里我们新增1变量，见 `ProtocolData.h`:

```c++
/******************** CmdID ***********************/
#define CMDID_POWER			0x0
#define CMDID_ANGLE			0x1	// 新增ID
/**************************************************/

typedef struct {
	BYTE power;
	BYTE angle;	// 新增变量，用于保存指针角度值
} SProtocolData;
```
**2).** 由于我们使用的还是前面定义的协议格式，所以这里协议解析的部分我们不需要做任何改动，只需在`procParse`中处理对应的CmdID值即可：

```c++
/**
 * 解析每一帧数据
 */
static void procParse(const BYTE *pData, UINT len) {
	// CmdID
	switch (MAKEWORD(pData[3], pData[2])) {
	case CMDID_POWER:
		sProtocolData.power = pData[5];
		break;

	case CMDID_ANGLE:	// 新增部分，保存角度值
		sProtocolData.angle = pData[5];
		break;
	}

	// 通知协议数据更新
	notifyProtocolDataUpdate(sProtocolData);
}
```
**3).** 我们再来看界面接收到协议数据的回调接口，见 logic/mainLogic.cc：

```c++
static void onProtocolDataUpdate(const SProtocolData &data) {
	// 串口数据回调接口

	// 设置仪表指针旋转角度
	mPointer1Ptr->setTargetAngle(data.angle);
}
```
完成以上流程后，接下来我们只需要通过MCU向屏发送相应的指令就可以看到仪表指针的旋转了；为了简单起见，我们这个程序里不做checksum校验，协议数据如下：
```c++
   帧头       CmdID    数据长度    角度值
0xFF 0x55   0x00 0x01   0x01     angle
```
我们可以在CommDef.h文件中打开`DEBUG_PRO_DATA`宏，打印接收到的协议数据：

![](https://ae01.alicdn.com/kf/HTB1ZL2ZaK6sK1RjSsrb760bDXXaP.png)

到此，串口的 **接收数据** ---> **解析数据** ---> **展示数据** 就算完成了； <br/><br/>
最后我们再来模拟一下串口**发送数据**；这里，我们给出的程序里，开启了一个定时器，2s模拟一次数据发送：

```c++
static bool onUI_Timer(int id) {
	// 模拟发送串口数据
	BYTE data = rand() % 200;
	sendProtocol(CMDID_ANGLE, &data, 1);

	return true;
}
```
以上代码其实就是模拟设置角度值，我们可以通过短接屏上通讯串口的TX和RX，实现**自发自收**，也是可以看到仪表指针旋转的； <br/><br/>
到此，我们的串口演示程序就介绍完了，开发人员可以先把演示程序编译烧录到机器里看一下效果，然后再在这基础之上增加一些协议，熟悉这整个通讯流程。
