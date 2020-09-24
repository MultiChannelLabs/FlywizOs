# Camera
The FlywizOS provides camera controls.

> [!Note]
>  Not all versions of the board support the camera function! If you need to use this function normally, please purchase a version that supports the USB camera function 

## How to use 
1. First, create a **camera** control, default background color is black. 
2. View the attribute table of **camera** 

   ![](assets/camera/properties.png)  

  Set Auto Preview to **On**  
  According to the connected camera model, select **CVBS** signal or not

3. Connect the camera to the board, and then download and run the program, you can see the camera preview screen.

   

## Start/Stop preview
We can start/stop the preview screen through source code.
* Start preview
```c++
mCameraView1Ptr->startPreview();
```
* Stop preview
```c++
mCameraView1Ptr->stopPreview();
```

## Photo camera

1. Implement the camera callback interface
  ```c++
  class PictureCallback : public ZKCamera::IPictureCallback {
  public:
      virtual void onPictureTakenStarted() {
        mTextView1Ptr->setText("Start taking a photo");
      }
      virtual void onPictureTakenEnd() {
        mTextView1Ptr->setText("End of photo");
      }
      virtual void onPictureTakenError() {
        mTextView1Ptr->setText("Photo error");
      }
      virtual const char* onPictureSavePath() {
          //Photo save path
          return "/mnt/extsd/camera.jpg";
      }
  };
  ```

2. Instantiate the interface and register
  ```c++
  //Defined as a global static variable
  static PictureCallback picture_callback;
  ```

3. Register the camera callback interface
  ```c++
  static void onUI_init(){
      mCameraView1Ptr->setPictureCallback(&picture_callback);
  }
  ```
  ```c++
  static void onUI_quit() {
    //Remember to empty the registration interface when the interface exits
      mCameraView1Ptr->setPictureCallback(NULL);
  }
  ```
4. Add a button, when you click the button, request a photo
  ```c++
  static bool onButtonClick_Button3(ZKButton *pButton) {
	  //Request a photo
	  mCameraView1Ptr->takePicture();
      return false;
  }
  ```

## Sample code
In this example, the camera preview and camera functions, and album functions are implemented.

For specific implementation, refer to [Sample Code](demo_download.md#demo_download) CameraDemo project

![](assets/camera/preview.png) 