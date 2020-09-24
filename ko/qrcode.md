# QR code
## QR code를 추가하는 방법
 QR code를 표시해야하는 경우 기존의 'QR code' 컨트롤을 사용하여 빠르게 구현할 수 있습니다. 구체적인 단계는 다음과 같습니다.

1. 더블 클릭하여 UI파일을 엽니다.
2. 우측의 컨트롤 박스에서 `QR code` 컨트롤을 찾습니다.
3. `QR code` 컨트롤을 마우스 왼쪽 버튼으로 누른 상태에서 원하는 위치로 드래그 한 후 왼쪽 버튼을 놓으면 QR code 컨트롤이 생성됩니다.
4. 방금 생성 한 QR code 컨트롤을 선택 후 우측의 속성 창에서 QR code의 내용을 수정하여 QR code 이미지가 동시에 변경되는 것을 볼 수 있습니다.

   ![](assets/QrCode-create.gif)

## QR code를 동적으로 업데이트
IDE를 통해 QR code 컨텐츠를 설정하는 것 외에도 코드를 통해 QR code 컨텐츠를 동적으로 설정할 수도 있습니다. 
```c++
bool loadQRCode(const char *pStr);
```
# Sample code
 ![](assets/qrcode/preview.png)  

더 자세한 사항은 [Sample Code](demo_download.md#demo_download)의 QrCodeDemo 프로젝트를 참고하십시오.