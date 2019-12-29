#pragma once
#include <iostream>
#include "BT.h"
#include "Graphviz.h"

#define M 3

void visit(KeyType key)
{
    cout << key << ' ';
}

void temp(BTree t)
{
    GraphRes *G = InitGraph();
    CreateGraph(t, G->g, NULL);
    RenderGraph(G);
    FreeGraph(G);
}

int main(int argc, char const *argv[])
{
    BTree t = NewTree(NULL, M);
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
    Delete(t, 50, M);
    temp(t);
    Delete(t, 53, M);
    temp(t);
    Delete(t, 37, M);
    temp(t);

    return 0;
}