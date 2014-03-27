#include "FIFO.h"
#include <stdio.h>

int main()
{
    FIFO<int> A(10);
	FIFO<double> B(10);
	A.Push(1);
    A.Push(2);
	B.Push(0.3);
    B.Push(0.4);
	printf("len: %d\n", A.GetLength());
	printf("exist 1? %d\n", A.Exist(1));
	printf("exist 3? %d\n", A.Exist(3));
	printf("Tail: %d\n", A.Pop());
	printf("empty? %d\n", A.Empty());
	printf("len: %d\n", A.GetLength());
	A.Clear();
	printf("len: %d\n", A.GetLength());
    
    printf("\n");
    printf("len: %d\n", B.GetLength());
	printf("exist 0.2? %d\n", B.Exist(0.2));
	printf("exist 0.3? %d\n", B.Exist(0.3));
	printf("Tail: %lf\n", B.Pop());
	printf("empty? %d\n", B.Empty());
	printf("len: %d\n", B.GetLength());
	B.Clear();
	printf("len: %d\n", B.GetLength());
    return 0;
}
