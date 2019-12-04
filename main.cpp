#include "BT.h"

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL, 3);
    BTree p;
    Insert(t, 30, 3);
    Insert(t, 37, 3);
    Insert(t, 26, 3);
    Search(t, 26);
    Search(t, 25);
    Search(t, 37);

    return 0;
}