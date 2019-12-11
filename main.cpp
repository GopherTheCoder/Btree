#include <iostream>
#include "BT.h"

void visit(KeyType key)
{
    cout << key << ' ';
}

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL, 3);
    BTree p;
    Insert(t, 30, 3);
    Insert(t, 37, 3);
    Insert(t, 26, 3);
    Insert(t, 26, 3);
    Traverse(t, visit);

    return 0;
}