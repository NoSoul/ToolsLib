#include "SlideWin.h"

int main()
{
    SlideWin<int> list0;
    SlideWin<int> list1;
    list0.ReSize(4);
    list1.ReSize(4);
    list0.Push(10);
    list0.Push(10);
    list0.Push(10);
    list0.Push(10);
    list1 = list0;
    list1.Push(20);
    if(*(list1.GetMax()) - * (list1.GetMin()) > 5) {
        printf("%d %d\n", list0.GetAvg(), list0.GetLength());
    }
    printf("%d\n", *(list1.Pop()));
    printf("%d\n", *(list1.Pop()));
    printf("%d\n", *(list1.Pop()));
    printf("%d\n", *(list1.Pop()));
    return 0;
}
