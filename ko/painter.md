
# Painter
 Painter 컨트롤은 간단한 기하학적 그리기 인터페이스를 제공합니다.

## 사용법
 **Painter** 컨트롤을 생성합니다. 기본 Painter 컨트롤은 투명합니다. 필요에 따라 배경 이미지를 추가하거나 배경 색을 수정할 수 있습니다.

   ![](assets/painter/properties.png)

## 코드 조작
**Painter** 컨트롤의 변수 포인터를 통해 함수들을 호출하여 그래픽을 그릴 수 있습니다.
이 컨트롤의 대부분의 함수들은 코드로 구현해야합니다. 예제는 다음과 같습니다.

```c++
static void onUI_init() {

    /**
     * Draw a rounded rectangle border
     */
    mPainter1Ptr->setLineWidth(4);
    mPainter1Ptr->setSourceColor(0x7092be);
    mPainter1Ptr->drawRect(10, 10, 430, 230, 5, 5);

    /**
     * Draw an arc
     */
    mPainter1Ptr->setLineWidth(3);
    mPainter1Ptr->setSourceColor(0xadc70c);
    mPainter1Ptr->drawArc(80, 80, 40, 40, -20, -120);

    /**
     * fill an arc
     */
    mPainter1Ptr->setLineWidth(3);
    mPainter1Ptr->setSourceColor(0x008ecc);
    mPainter1Ptr->fillArc(80, 80, 40, 40, -20, 120);


    /**
     * Draw triangle
     */
    mPainter1Ptr->setLineWidth(4);
    mPainter1Ptr->setSourceColor(0xff804f);
    mPainter1Ptr->drawTriangle(200, 40, 160, 90, 240, 90);//空心三角形
    mPainter1Ptr->fillTriangle(300, 40, 260, 90, 340, 90); //实心三角形

    /**
     * Draw straight line
     */
    MPPOINT points1[] = {
            {50 , 150},
            {150, 150},
            {70 , 200},
            {100, 120},
            {130, 200},
            {50 , 150}
    };
    /** Connect to a line according to the provided coordinates of multiple points */
    mPainter1Ptr->setLineWidth(2);
    mPainter1Ptr->setSourceColor(0x88cffa);
    mPainter1Ptr->drawLines(points1, TABLESIZE(points1));


    /**
     * Draw a curve
     */
    MPPOINT points2[] = {
            {250, 150},
            {350, 150},
            {270, 200},
            {300, 120},
            {330, 200},
            {250, 150}
    };
    mPainter1Ptr->setLineWidth(3);
    mPainter1Ptr->setSourceColor(0xe28ddf);
    /** Connect as a curve according to the provided multiple point coordinates */
    mPainter1Ptr->drawCurve(points2, TABLESIZE(points2));
}
```
# Sample code
**Painter** 컨트롤의 사용을 보여줍니다.

![](assets/painter/preview.png) 

 더 자세한 사항은 [Sample Code](demo_download.md#demo_download)의 `PainterDemo`를 참고하십시오.