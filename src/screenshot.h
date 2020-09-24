#ifndef JNI_SCREENSHOT_H_
#define JNI_SCREENSHOT_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <Utils/Log.h>
#include <string.h>
#include <errno.h>
#include "utils/Log.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;
//typedef unsigned int DWORD;
typedef long LONG;


typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
}__attribute__((packed)) BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
}__attribute__((packed)) BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
}__attribute__((packed)) RGBQUAD;


#define FRAME_BUFFER_PATH                "/dev/fb0"
#define FRAME_BUFFER_PATH2                "/dev/graphics/fb0"


class Screenshot {
public:
  static bool Save(const char* path) {
    return Capture(path);
  }

  static bool AutoSave() {
    static int i = 0;
    char buf[1024] = {0};
    ++i;
    //默认保存到TF卡目录下
    snprintf(buf, sizeof(buf), "/mnt/extsd/screenshot%02d.bmp", i);
    return Capture(buf);
  }



private:
  static bool Capture(const char* path) {
    if (path == NULL) {
      return false;
    }
    if (strstr(path, ".bmp") == NULL) {
      //仅支持保存为bmp格式图片
      return false;
    }

    int img_fd = -1, fb_fd = -1;
    int data_size = 0;
    char *img_buf = NULL;
    struct fb_var_screeninfo var_info;
    BITMAPFILEHEADER file_head;
    BITMAPINFOHEADER info_head;
    /*open files*/
    fb_fd = open(FRAME_BUFFER_PATH, O_RDWR);
    if (fb_fd < 0) {
      fb_fd = open(FRAME_BUFFER_PATH2, O_RDWR);
    }
    if (fb_fd < 0) {
      LOGE("open framebuff %s", strerror(errno));
      return false;
    }
    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &var_info) < 0) {
      LOGE("ioctl FBIOGET_VSCREENINFO");
      LOGE("ioctl FBIOGET_VSCREENINFO");
      close(img_fd);
      return false;
    }
    LOGE("xres %d, yres %d\n", var_info.xres, var_info.yres);
    img_fd = open(path, O_RDWR | O_CREAT, 0644);
    if (img_fd < 0) {
      LOGE("open image failed");
      close(img_fd);
      return false;
    }

    data_size = var_info.xres * var_info.yres * (var_info.bits_per_pixel / 8);
    /*initialize bmp structs*/
    file_head.bfType = 0x4d42;
    file_head.bfSize = sizeof(file_head) + sizeof(info_head) + data_size;
    file_head.bfReserved1 = file_head.bfReserved2 = 0;
    file_head.bfOffBits = sizeof(file_head) + sizeof(info_head);

    info_head.biSize = sizeof(info_head);
    info_head.biWidth = var_info.xres;
    info_head.biHeight = var_info.yres;
    info_head.biPlanes = 1;
    info_head.biBitCount = var_info.bits_per_pixel;
    info_head.biCompression = 0;
    info_head.biSizeImage = 0;
    info_head.biXPelsPerMeter = 0;
    info_head.biYPelsPerMeter = 0;
    info_head.biClrUsed = 0;
    info_head.biClrImportant = 0;

    img_buf = (char *) malloc(data_size);
    if (img_buf == NULL) {
      LOGE("malloc failed!\n");
      close(fb_fd);
      close(img_fd);
      return false;
    }

    /*read img data and */
    read(fb_fd, img_buf, data_size);

    write(img_fd, &file_head, sizeof(file_head));
    write(img_fd, &info_head, sizeof(info_head));

    /*revese img and write to file*/
    for (size_t i = 0; i < var_info.yres; i++) {
      write(img_fd,
          img_buf
              + var_info.xres * (var_info.yres - i - 1)
                  * (var_info.bits_per_pixel / 8),
          var_info.xres * (var_info.bits_per_pixel / 8));
    }

    close(fb_fd);
    close(img_fd);
    sync();
    if (img_buf != NULL) {
      free(img_buf);
    }
    return true;
  }
private:
  Screenshot() {

  }
};

#endif /* JNI_SCREENSHOT_H_ */
