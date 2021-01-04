
# 字体库设置
FlywizOS系统默认打包的字体库是**Consolas**，我们可以查看项目属性：

![](images/font_setting.png)

字体选项默认勾上，编译生成的升级文件就会打包工具安装目录下相应平台**font**目录下的**fzcircle.ttf**字体库

![](images/font_path.png)

如果我们想使用其他字体库，只需去除默认选项，导入新的字体库即可（**注意，这里字体库仅支持ttf格式**）：

![](images/load_ttf.gif)