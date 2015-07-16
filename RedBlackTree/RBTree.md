# 红黑树
红黑树是一种特殊的二叉树，由于是自平衡的，所以可以在O(logN)内实现插入、查找和删除的操作。
红黑树的叶子节点本身不包含任何数据，完全可以使用NULL来表示，但是如果明确表示一个叶子节点的话会对算法有简化的作用，为了减少内存相关的操作，所有的叶子节点可以专门使用一个节点来表示。

### 特性
* 所有的节点为黑色或红色。
* 根节点以及所有叶子节点为黑色。
* 每个红色节点的左右孩子节点都是黑色。
* 从任一节点到其每个叶子节点的所有简单路径都包含相同数目的黑色节点（一个没有重复顶点的道路称为简单路径）

根据这些特性可以得到一个结论：从根节点到其最远叶子节点的距离不会比到其最近叶子节点的距离的两倍长（结合特性3和4）。所以红黑树高度上大致是平衡的。因为插入、查找和删除的操作的时间跟高度成比例，所以红黑树保证了高效的插入、查找和删除操作。红黑树不保证重量平衡，所以同级兄弟节点之间子节点的数量差距会有很大的情况。


### 树旋转
对子树进行调整，每次旋转不影响对该二叉树的中序遍历的结果，通常用于调整树的平衡性。

            +++++                             +++++
            | A |                             | B |
            +++++                             +++++
            /   \                             /   \
        +++++   +++++                     +++++   +++++
        | B |   | C |  Right Rotation ->  | E |   | A |
        +++++   +++++  <- Left Rotation   +++++   +++++
        /   \                                     /   \
    +++++   +++++                             +++++   +++++
    | E |   | F |                             | F |   | C |
    +++++   +++++                             +++++   +++++
    
    红色节点 黑色节点 根节点为黑色的子树 任意颜色节点
    -----    +++++     /+\               +++++
    |   |    +   +    /   \              |   |
    -----    +++++    +++++              +++++
中序遍历:EBFAC
### 插入操作
* 先进行普通二叉搜索树的插入操作
* 对新节点进行染色，如果新节点为黑色，将违反性质4，所以将新节点染为红色，当新节点N的父节点P不为黑色时，则需要考虑以下情况进行平衡调整
* 当节点N位于树的根上时，只需要将节点N的颜色标记为黑即可
* 当节点N的叔父节点S为红色时，将它们父节点P和叔父节点S重绘为黑色并重绘祖父节点G为红色，由于祖父节点G的父节点也可能是红色，所以需要针对祖父节点递归整个插入调整平衡过程

            +++++              -----
            + G +              | G |
            +++++              -----
            /   \              /   \
        -----   -----      +++++   +++++
        | P |   | S |  ->  + P +   + S +
        -----   -----      +++++   +++++
          |                  |
        -----              -----
        | N |              | N |
        -----              -----
* 当节点N的叔父节点S为黑色时，由于P和N都为红色，所以必须进行平衡调整，由于树旋转的特点，当新节点N跟父节点P的对应关系与父节点P跟祖父节点G的对应关系不同时，通过树旋转调换新节点N与父节点P，使得N跟P的对应关系与P跟G的对应关系相同

                +++++                       +++++
                + G +                       + G +
                +++++                       +++++
                /   \                       /   \
            -----   +++++               -----   +++++
            | P |   + S +               | N |   + S +
            -----   +++++               -----   +++++
            /   \           ->          /   \
         /+\    -----               -----    /+\ 
        / 1 \   | N |               | P |   / 3 \
        +++++   -----               -----   +++++
                /   \               /   \
             /+\     /+\         /+\     /+\
            / 2 \   / 3 \       / 1 \   / 2 \
            +++++   +++++       +++++   +++++
* N跟P的对应关系与P跟G的对应关系相同时，进行树旋转使得以前的父节点P现在是新节点N和以前的祖父节点G的父节点，然后交换以前的父节点P和祖父节点G的颜色

                +++++              +++++ 
                + G +              + P +
                +++++              +++++
                /   \              /   \
            -----   +++++      -----   -----
            | P |   + S +  ->  | N |   | G |
            -----   +++++      -----   -----
            /   \                      /   \
        -----    /+\                /+\    +++++
        | N |   / 1 \              / 1 \   + S +
        -----   +++++              +++++   +++++
### 删除操作
当删除的节点N时，如果N有两个非叶子节点，则找出N的直接前趋或直接后继节点Y，然后考虑删除节点Y，否则考虑删除节点N
* 删除节点N，将N的子节点放到N的位置上
* 删除节点Y，先将Y的子节点M放到Y的位置上，然后将Y放到节点N的位置上，颜色仍然为节点N的颜色
* 如果要删除的节点的颜色为黑色，则需要考虑以下情况进行平衡调整(设要被删除的节点X的子节点为M，X的兄弟节点为S，X的父节点为P，L为S的左孩子，R为S的右孩子)
    * 当M为树根的位置上或M为红色时，只要M黑色就满足所有性质
    * 当P黑S红时，通过树旋转，并交换P和S的颜色，就能得到P红S黑的情况

                +++++                      +++++
                + P +                      + S +
                +++++                      +++++
                /   \                      /   \
            +++++   -----              -----   +++++
            + M +   | S |      ->      | P |   + R +
            +++++   -----              -----   +++++
                    /   \              /   \
                +++++   +++++      +++++   +++++
                + L +   + R +      + M +   + L +
                +++++   +++++      +++++   +++++
    * 由于删除了节点X导致所有通过M的节点的黑色节点数都少了一，当L和R都为黑时，只要将S改为红色，这样所有通过S的节点就跟所有通过M的节点一样，简单路径都少一，然后针对节点P进行平衡调整（首先P为任意颜色不影响当前处理）

                +++++                  +++++
                | P |                  | P |
                +++++                  +++++
                /   \                  /   \
            +++++   +++++          +++++   -----
            + M +   + S +      ->  + M +   | S |
            +++++   +++++          +++++   -----
                    /   \                  /   \
                +++++   +++++          +++++   +++++
                + L +   + R +          + L +   + R +
                +++++   +++++          +++++   +++++
    * 当L为红色，R为黑色时，通过树旋转，再交换L和S的颜色，能得到S为黑色且右孩子为红色情况
    
                +++++                  +++++
                | P |                  | P |
                +++++                  +++++
                /   \                  /   \
            +++++   +++++          +++++   +++++
            + M +   + S +      ->  + M +   + L +
            +++++   +++++          +++++   +++++
                    /   \                  /   \
                -----   +++++           /+\    -----
                | L |   + R +          / 1 \   | S |
                -----   +++++          +++++   -----
                /   \                          /   \
             /+\     /+\                   /+\     +++++
            / 1 \   / 2 \                 / 2 \    + R +
            +++++   +++++                 +++++    +++++
    * 当R为红色时，通过树旋转以及交换S和P颜色、更改R的颜色，由于P最终为黑色所有通过M/L的节点的所有简单路路径上的黑色节点数与删除节点X之前一致，所有通过R的节点性质4也仍然保持，又因为最终S的颜色与P的颜色一致，因此当前情况下可以结束调整了。

                +++++                      +++++
                | P |                      | S |
                +++++                      +++++
                /   \                      /   \
            +++++   +++++              +++++   +++++
            + M +   + S +      ->      + P +   + R +
            +++++   +++++              +++++   +++++
                    /   \              /   \
                +++++   -----      +++++   +++++
                | L |   | R |      + M +   | L |
                +++++   -----      +++++   +++++