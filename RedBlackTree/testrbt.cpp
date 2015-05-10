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
        struct RBNode_t *node = (struct RBNode_t *)malloc(sizeof(struct RBNode_t));
        node->mKey.mPrimaryVal = num;
        RBTreeInsert(&Tree, node);
    }
    //RBTreeInorder(Tree.mTreeRoot, &(Tree.mSentinelLeaf));
    for(int i = 0; i < N - 10; ++i) {
        int num;
        do {
            num = rand() % N;
        } while(!Flag[num]);
        Flag[num] = false;
        RBData_t key;
        key.mPrimaryVal = num;
        struct RBNode_t *node = RBTreeSearch(Tree.mTreeRoot, &key, &(Tree.mSentinelLeaf));
        RBTreeDelete(&Tree, node);
        free(node);
    }
    RBTreeDestroy(&Tree);
    return 0;
}
