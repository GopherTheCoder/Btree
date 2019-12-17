#include <iostream>
#include "BT.h"

#define M 3

void visit(KeyType key)
{
    cout << key << ' ';
}

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL, M);
    BTree p;
    Insert(t, 45, M);
    Insert(t, 24, M);
    Insert(t, 53, M);
    Insert(t, 61, M);
    Insert(t, 3, M);
    Insert(t, 37, M);
    Insert(t, 50, M);
    Insert(t, 90, M);
    Insert(t, 100, M);
    Insert(t, 70, M);
    Insert(t, 12, M);

    Delete(t, 12, M);
    Delete(t, 45, M);

    return 0;
}