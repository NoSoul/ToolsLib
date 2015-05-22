#include "LogSet.h"

LogType::LogType()
{
    logtoscrn = false;
    logtofile = false;
}

bool LogType::IsLogToScrn()
{
    return logtoscrn;
}

bool LogType::IsLogToFile()
{
    return logtofile;
}

void LogType::SetLogToScrn(bool newstate)
{
    logtoscrn = newstate;
}

void LogType::SetLogToFile(bool newstate)
{
    logtofile = newstate;
}

void LogType::SetBoth(bool newscrn, bool newfile)
{
    logtoscrn = newscrn;
    logtofile = newfile;
}

LogSet *LogCenter = LogSet::GetInstance();

LogSet::LogSet()
{
}

LogSet *LogSet::GetInstance()
{
    static LogSet handle;
    return (&handle);
}
