#include "BT.h"

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL,3);
    __SimpleInsert(t, 30);
    __SimpleInsert(t, 37);
    __SimpleInsert(t, 26);
    __RootSplit(t);

    return 0;
}