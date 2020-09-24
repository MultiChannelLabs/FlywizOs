
# Font setting
The default font library packaged in FlywizOS system is **思源黑体字体库**, we can view the project properties:

![](images/font_setting.png)

The font option is checked by default, and the compiled upgrade file will be packaged in the **fzcircle.ttf** font library in the **font** directory of the corresponding platform in the tool installation directory

![](images/font_path.png)

This font library is **思源黑体字体库**, we made some cropping and renamed it **fzcircle.ttf**<br/>
If we want to use other font libraries, just remove the default options and import a new font library (**Note that this font library only supports ttf format**) :

![](images/load_ttf.gif)

**Z6S and later platforms** Our system has built-in **fzcircle.ttf** font library directly, the purpose is to speed up the boot speed, if any fonts are missing, we need to customize an extended font library by ourselves, the same as **思源黑体字体**, the name of the font library is also **fzcircle.ttf**, the import method is the same as above, so that when the system loads fonts, the built-in fonts in the system are loaded first, and the corresponding fonts in the extended font library are loaded if the loading fails; if you want to use other fonts Library, the name of the imported font library does not need to be called **~~fzcircle.ttf~~**, so the loaded fonts are all external fonts.<br/>

Conclusion:<br/>
**Z11S platform**: Because the platform system does not have a built-in font library, the system directly uses the font library packaged by the tool. There is no extension of the font library. Remember, the default package is the **思源黑体字体**;<br/>
**Z6S and later platforms**: The system has a built-in **fzcircle.ttf** font library, supports extended font library, the same as **思源黑体字体**, the name of the font library must be **fzcircle.ttf**; When using other font libraries, the name of the imported font library cannot be **~~fzcircle.ttf~~**;

