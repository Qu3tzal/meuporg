#ifndef KANTAN_PLATFORM
#define KANTAN_PLATFORM

// Uncomment this line to port Kantan to android.
//#define KANTAN_ANDROID 1

#ifdef KANTAN_ANDROID
#include <android/log.h>
#define APPNAME "Kantan"
#endif // KANTAN_ANDROID

#endif // KANTAN_PLATFORM

