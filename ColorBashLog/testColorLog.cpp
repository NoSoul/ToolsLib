#include "ColorBashLog.h"

int main()
{
    ColorLog::GetIntance()->Msg(LOG_INFO, "Hello\n");
    ColorLog::GetIntance()->Msg(LOG_WARNING, "Hello\n");
    ColorLog::GetIntance()->Msg(LOG_DEBUG, "Hello\n");
    ColorLog::GetIntance()->Msg(LOG_ERROR, "Hello\n");
    ColorLog::GetIntance()->Msg(LOG_FATAL, "Hello\n");

    ColorLog::GetIntance()->Msg(LOG_INFO, "Hello %d\n", LOG_INFO);
    ColorLog::GetIntance()->Msg(LOG_WARNING, "Hello %d\n", LOG_WARNING);
    ColorLog::GetIntance()->Msg(LOG_DEBUG, "Hello %d\n", LOG_DEBUG);
    ColorLog::GetIntance()->Msg(LOG_ERROR, "Hello %d\n", LOG_ERROR);
    ColorLog::GetIntance()->Msg(LOG_FATAL, "Hello %d\n", LOG_FATAL);

    ColorLog::GetIntance()->Msg(LOG_INFO, "Hello %d %d\n", LOG_INFO, 0);
    ColorLog::GetIntance()->Msg(LOG_WARNING, "Hello %d %d\n", LOG_WARNING, 0);
    ColorLog::GetIntance()->Msg(LOG_DEBUG, "Hello %d %d\n", LOG_DEBUG, 0);
    ColorLog::GetIntance()->Msg(LOG_ERROR, "Hello %d %d\n", LOG_ERROR, 0);
    ColorLog::GetIntance()->Msg(LOG_FATAL, "Hello %d %d\n", LOG_FATAL, 0);
    return 0;
}
