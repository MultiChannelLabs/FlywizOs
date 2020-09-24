When we create a new project, there is a Main.cpp file in the generated template code, path: jni/Main.cpp; the template code is as follows:

![](images/Screenshotfrom2018-06-06182629.png)

The code in the red box is the startup interface code, and the interface is **mainActivity**. The corresponding UI resource file is **main.ftu**. Specifically, we can look at the code in jni/activity/mainActivity.cpp. It is clear which UI resource is corresponding:

![](images/Screenshotfrom2018-06-06183808.png)

