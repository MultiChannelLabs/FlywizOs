
# Font setting
FlywizOS IDE의 기본 폰트는 **思源黑体字体库**입니다.

![](images/font_setting.png)

폰트의 옵션이 **Default**로 설정되어 있으면, 컴파일 및 업데이트 파일 생성 시 내장된 기본 폰트인 **fzcircle.ttf**가 포함됩니다.

![](images/font_path.png)

> 만약 다른 폰트를 사용하고 싶다면, **Default** 체크 옵션을 해제하고 새로운 폰트를 설정하십시오. (**Note : ttf 포맷의 폰트만 지원 가능**) :

![](images/load_ttf.gif)

 **Z6S and later platforms** Our system has built-in **fzcircle.ttf** font library directly, the purpose is to speed up the boot speed, if any fonts are missing, we need to customize an extended font library by ourselves, the same as **思源黑体字体**, the name of the font library is also **fzcircle.ttf**, the import method is the same as above, so that when the system loads fonts, the built-in fonts in the system are loaded first, and the corresponding fonts in the extended font library are loaded if the loading fails; if you want to use other fonts Library, the name of the imported font library does not need to be called **~~fzcircle.ttf~~**, so the loaded fonts are all external fonts.<br/>

Conclusion:<br/>
**Z11S platform**: Because the platform system does not have a built-in font library, the system directly uses the font library packaged by the tool. There is no extension of the font library. Remember, the default package is the **思源黑体字体**;<br/>
**Z6S and later platforms**: The system has a built-in **fzcircle.ttf** font library, supports extended font library, the same as **思源黑体字体**, the name of the font library must be **fzcircle.ttf**; When using other font libraries, the name of the imported font library cannot be **~~fzcircle.ttf~~**;

