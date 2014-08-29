#include "ColorBashLog.h"

ColorLog *ColorLog::mHandle = NULL;

ColorLog::ColorLog()
{
    color[LOG_INFO] = COLOR8_White;
    color[LOG_WARNING] = COLOR8_Green;
    color[LOG_DEBUG] = COLOR8_Yellow;
    color[LOG_ERROR] = COLOR8_Red;
    color[LOG_FATAL] = COLOR8_Blue;
}

int ColorLog::Msg(e_LogType type, const char *format, ...)
{
    sprintf(Str, "\E[%dmLOG::%d %s\E[0m", color[type], type, format);
    va_list arg;
    int done;
    va_start(arg, format);
    done = vfprintf (stdout, Str, arg);
    va_end(arg);
    return done;
}

ColorLog *ColorLog::GetIntance()
{
    if(mHandle == NULL)
    {
        mHandle = new ColorLog();
    }
    return mHandle;
}
