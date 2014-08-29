#ifndef _COLOR_BASH_H_
#define _COLOR_BASH_H_
#define COLOR8_Black    30
#define COLOR8_Red      31
#define COLOR8_Green    32
#define COLOR8_Yellow   33
#define COLOR8_Blue     34
#define COLOR8_Violet   35
#define COLOR8_Cyan     36
#define COLOR8_White    37
#include <stdio.h>
#include <stdarg.h>
typedef enum
{
    LOG_INFO=0,
    LOG_WARNING,
    LOG_DEBUG,
    LOG_ERROR,
    LOG_FATAL
} e_LogType;
class ColorLog
{
    private:
        int color[5];
        char Str[10000];
        ColorLog();
    public:
        ~ColorLog();
        static ColorLog *mHandle;

        int Msg(e_LogType , const char *, ...);
        static ColorLog *GetIntance();
};
#endif
