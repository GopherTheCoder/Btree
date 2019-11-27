#include "BT.h"

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL, 3);
    __Insert(t, 30, 3);
    __Insert(t, 37, 3);
    __Insert(t, 26, 3);
    Search(t, 30);
    Search(t, 25);
    Search(t, 26);

    return 0;
}