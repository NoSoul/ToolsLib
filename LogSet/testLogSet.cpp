#include "LogSet.h"

void Show()
{
    if(LogCenter->nosoul.IsLogToScrn())
    {
        puts("Hello.");
        printf("OK. %d\n", 0);
    }
    if(LogCenter->nosoul.IsLogToFile())
    {
        FILE *fw;
        fw = fopen("data.dat", "w");
        fputs("Hello.\n", fw);
        fprintf(fw, "OK.\n", 0);
        fclose(fw);
    }
}

int main()
{
    Show();
    LogCenter->nosoul.SetLogToScrn(true);
    Show();
    LogCenter->nosoul.SetLogToFile(true);
    Show();
    return 0;
}
