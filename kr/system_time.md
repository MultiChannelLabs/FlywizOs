# 시스템 시간
* 필요한 헤더 파일

```c++
#include "utils/TimeHelper.h"
```
  > tm 구조체의 각 변수에 대한 설명

```c++
struct tm {
    int tm_sec; /* second - the value range is [0,59] */
	int tm_min; /* minute - the value range is [0,59] */
	int tm_hour; /* hour - the value range is [0,23] */
	int tm_mday; /* Day of the month - the value range is[1,31] */
	int tm_mon; /* Month (starting from January, 0 means January) - the value range is[0,11] */
	int tm_year; /* Year, the value starts from 1900 */
    ...
}
```

* 현재 날짜 및 시간 가져오기

```c++
struct tm *t = TimeHelper::getDateTime();
```

* 시간 표시 예제

```c++
static void updateUI_time() {
    char timeStr[20];
    static bool bflash = false;
    struct tm *t = TimeHelper::getDateTime();

    sprintf(timeStr, "%02d:%02d:%02d", t->tm_hour,t->tm_min,t->tm_sec);
    mTextTimePtr->setText(timeStr); // Pay attention to modify the control name

    sprintf(timeStr, "%d / %02d / %02d", 1900 + t->tm_year, t->tm_mon + 1, t->tm_mday);
    mTextDatePtr->setText(timeStr); // Pay attention to modify the control name

    static const char *day[] = { "Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Friu", "Sat." };
    sprintf(timeStr, "day of the week %s", day[t->tm_wday]);
    mTextWeekPtr->setText(timeStr); // Pay attention to modify the control name
}
```



* 시간 설정 예제

```c++
// Use tm structure to set time
static void setSystemTime() {
	struct tm t;
	t.tm_year = 2017 - 1900;
	t.tm_mon = 9 - 1;
	t.tm_mday = 13;
	t.tm_hour = 16;
	t.tm_min = 0;
	t.tm_sec = 0;

	TimeHelper::setDateTime(&t);
}

// Or set the time with a string  date str format: 2017-09-13 16:00:00
TimeHelper::setDateTime("2017-09-13 16:00:00");
```

더 자세한 내용은 [**Sample Code**](demo_download.md#demo_download)를 참고하십시오.
