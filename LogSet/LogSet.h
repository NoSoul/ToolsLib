#ifndef _LogSet_H_
#define _LogSet_H_
#include <stdio.h>
class LogType
{
private:
    bool logtoscrn;
    bool logtofile;
public:
    LogType();
    bool IsLogToScrn();
    bool IsLogToFile();
    void SetLogToScrn(bool );
    void SetLogToFile(bool );
    void SetBoth(bool , bool );
};

class LogSet
{
private:
    LogSet();
    static LogSet *handle;
public:
    static LogSet *GetInstance();

    LogType nosoul;
};
extern LogSet *LogCenter;
#endif
