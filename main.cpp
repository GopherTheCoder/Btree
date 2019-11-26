#include "BT.h"

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL,3);
    __Insert(t, 30, 3);
    __Insert(t, 37, 3);
    __Insert(t, 26, 3);

    return 0;
}