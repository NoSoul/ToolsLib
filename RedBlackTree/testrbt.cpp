#include "rbt.h"
#include <string.h>

int main()
{
    const int N = 1000000;
    bool Flag[N];
    RBTree_t Tree;
    memset(Flag, 0, sizeof(Flag));
    RBTreeInitialize(&Tree);
    for(int i = 0; i < N; ++i) {
        int num;
        do {
            num = rand() % N;
        } while(Flag[num]);
        Flag[num] = true;
        RBTreeAdd(&Tree, num);
    }
    //RBTreeInorder(Tree.mTreeRoot, &Tree.mSentinelLeaf);
    for(int i = 0; i < N - 10; ++i) {
        int num;
        do {
            num = rand() % N;
        } while(!Flag[num]);
        Flag[num] = false;
        RBTreeDel(&Tree, num);
    }
    RBTreeDestroy(&Tree);
    return 0;
}
