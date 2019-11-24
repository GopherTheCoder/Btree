#include <cstdlib>

using namespace std;

typedef int KeyType;
typedef struct BTNode
{
    int n;
    struct BTNode *parent;
    KeyType *key;
    struct BTNode **children;
} BTNode, *BTree;

BTree NewTree(KeyType key, BTNode *parentNode, int m)
{
    BTree node = (BTree)malloc(sizeof(BTNode));
    node->n = 1;
    node->parent = parentNode;
    node->key = (KeyType *)calloc(m + 1, sizeof(KeyType));
    node->key[1] = key;
    node->children = (BTree *)calloc(m + 1, sizeof(BTree));

    return node;
}

void __SimpleInsert(BTNode *node, KeyType key) // 简单无脑插入，结果可能需分裂
{
    node->n++;
    // 按顺序插入
    int i;
    for (i = 1; i < n; i++)
        if (node->key[i] > key)
            break;

    for (int j = n; j > i; j--)
        node->key[j] = node->key[j - 1];
    node->key[i] = key;
}

void __Split(BTNode *node) // 分裂，仅在分裂时使用
{
    
}