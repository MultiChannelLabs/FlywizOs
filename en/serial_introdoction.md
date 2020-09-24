# Introduction to the serial port
The picture below is the simplest communication model. The screen and MCU communicate through the serial port, as long as the protocol is established between them, they can interact.

![](images/serial_model.png)

Note - The traditional serial screens are used as slave devices and control them by sending corresponding instructions through the MCU. Our serial screens are different. Our screens are logical, and It can realize the interaction by itself, here as the host side.

If you develop this part of the communication code from beginning, the workload will be huge. In order to simplify the development process and enable developers to pay more attention to the development of business logic, our tool will automatically generate the serial communication code when building a new project. 

![](images/Screenshotfrom2018-06-06160506.png)

At the same time, we also provide a callback interface for protocol data and activity interaction:

![](images/Screenshotfrom2018-06-06162409.png)

Developers pay more attention to the display of data on the UI interface, while the communication part is automatically completed by our framework.
The protocol analysis part of the communication framework needs to be changed according to the communication protocol used by the developer. In the next chapter of [Communication Framework Explanation](serial_framework.md), we will focus on the principle and the parts that need to be modified, and deepen our understanding of this communication framework through some cases in this chapter of [Communication Case Practice](serial_example.md).