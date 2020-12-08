

#  円形プログレスバー
特定のアプリケーションの場合は、「一直線のプログレスバー"より"円形のプログレスバー」がより適していることがあります。 

## 使い方 
1. まず、UIファイルをオープンした後、**circular progress bar**コントロールを作成します。そして**valid picture**属性に画像を追加すると、基本的なラウンドプログレスバー完成されます。
    원형 프로그래스 바의 모든 속성은 아래와 같습니다.

   ![](assets/circlebar/property.png)

2. 円形プログレスバーは、現在のプログラスが扇形領域で表示され、この領域は、**valid picture**の一定領域のみ表示することで実装されます。 たとえば、もし属性が上の画像のように設定された場合、最大値は100であり、初期の開始角度は0であり、プログラスの方向は時計回りです。その後、プログラスを25に設定すると、唯一の0から90°の扇形領域に対応するvalid pictureのみ表示されます。そして、もしプログラスが100であれば、全体valid pictureが表示されます。

> Note: プログラス値に応じた表示領域の変更は、**valid picture**のみ適用され、**background picture**は適用されません。

   ![](assets/circlebar/location.png)



## 運用コード

円形プログレスバーで提供される関数は非常に単純です。
```
//Set current progress
void setProgress(int progress);
//Get current progress
int getProgress()；

//Set maximum progress
void setMax(int max);
//Get maximum progress
int getMax()；
```



# サンプルコード

例では、上部スライドバーを調整すると、次の2つの円形のプログレスバーが変更されます。

[Sample code](demo_download.md＃demo_download)のCircleBarDemoプロジェクト参照してください。

![](assets/circlebar/preview.png)  
