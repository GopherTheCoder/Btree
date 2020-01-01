#pragma once
#include <iostream>
#include "headers.h"

#define M 3

using namespace std;

void visit(KeyType key)
{
    cout << key << ' ';
}

void temp(BTree t)
{
    GraphRes *G = Graph::InitGraph();
    Graph::CreateGraph(t, G->g, NULL);
    Graph::RenderGraph(G);
    Graph::FreeGraph(G);
}

int main(int argc, char const *argv[])
{
    BTree t = BT::NewTree(NULL, M);
    BT::Insert(t, 45, M);
    BT::Insert(t, 24, M);
    BT::Insert(t, 53, M);
    BT::Insert(t, 61, M);
    BT::Insert(t, 3, M);
    BT::Insert(t, 37, M);
    BT::Insert(t, 50, M);
    BT::Insert(t, 90, M);
    BT::Insert(t, 100, M);
    BT::Insert(t, 70, M);
    BT::Insert(t, 12, M);

    BT::Delete(t, 12, M);
    BT::Delete(t, 50, M);
    temp(t);
    BT::Delete(t, 53, M);
    temp(t);
    BT::Delete(t, 37, M);
    temp(t);

    return 0;
}