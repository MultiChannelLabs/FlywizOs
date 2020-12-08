# 하드웨어 사용 설명
## 使用前注意事项
1. 确定电源电压一定为4.5-5.5V。如果电源超过高于或者低于这个范围，机器无法工作正常，如果电源电压过高，会损坏模组屏。
2. 确定好串口电平是RS232还得TTL还是RS485，根据要求结合第4点说明选择。
3. 注意电源接口座的接口定义说明，不要接错。

## 模组功能接口示意图  
* ### z11s
  ![](assets/hardware/z11s.png)
* ### z6s  
  ![](assets/hardware/z6s.png) 
  
## 电源接口说明  
* ### PH2.0-8PIN座子接口定义

   | 1PIN | 2PIN |3PIN | 4PIN | 5PIN | 6PIN | 7PIN | 8PIN |
| --- | --- | --- | --- |--- | --- |--- | --- |
| DC5V | RESET | CTS | TXOUT/B | RXIN/A | RTS | GND | GND |
|直流电源输入4.5-5.5V |模组RESET,默认是NC  |流控CTS  |串口TX或者RS485-B。（接外部设备RX/RS485B） |串口RX或者RS485-A（接外部设备TX/RS485A）| 流控RTS|  电源地 |电源地 |

<br/>
*  ### 10PIN1.0FPC座子接口定义  

    | 1/2/3PIN | 4PIN | 5PIN | 6PIN | 7PIN | 8/9/10PIN |
    | --- | --- | --- | --- |--- | --- |
    | DC5V | RTS | RXIN/A | TXOUT/B | CTS | GND |
    |直流电源输入4.5-5.5V | 流控RTS | 串口RX或者RS485-A（接外部设备TX/RS485A）| 串口TX或者RS485-B。（接外部设备RX/RS485B） | 流控CTS |  电源地 |
    
    
    
## 串口输出方式选择  
如图说明  
0R电阻是TTL，0R不要是RS232。  

 ![](https://ae01.alicdn.com/kf/HTB15NSoNzTpK1RjSZKP7613UpXat.png) 

## 模组屏对应外部设备接口示意图

 ![](https://ae01.alicdn.com/kf/HTB1KimmNxTpK1RjSZFK7612wXXaZ.png) 

## 样品配送电源线说明

 电源线为单端PH2.0-8PIN 10CM带扣的白蓝或者白红线。如图    

  ![](https://ae01.alicdn.com/kf/HTB1.xrlau3tHKVjSZSg7604QFXaV.png)   
  ![](https://ae01.alicdn.com/kf/HTB13RdNNCzqK1RjSZPc762TepXav.png) 