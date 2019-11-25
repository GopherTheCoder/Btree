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

int __SimpleInsert(BTNode *node, KeyType key) // 简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
{
    node->n++;
    // 按顺序插入
    int i;
    for (i = 1; i < n; i++)
        if (node->key[i] > key)
            break;

    for (int j = node->n; j > i; j--)
        node->key[j] = node->key[j - 1];
    node->key[i] = key;

    return i;
}

void __OrderedInsert(BTNode *node, KeyType key) // 已有序插入，仅在确保输入有序时使用
{
    node->n++;

    node->key[node->n] = key;
}

bool __Split(BTNode *node) // 分裂，仅在分裂时使用
{
    int m = node->n;
    BTree parent = node->parent;

    // 新结点处理
    BTree newNode = NewTree(node->key[(m + 3) / 2], parent, m); // 新结点
    for (int i = (m + 5) / 2; i <= m; i++)                      // 插入剩余关键字
        __OrderedInsert(newNode, node->key[i]);
    for (int i = (m + 1) / 2; i <= m; i++) // 插入所有子树
        newNode->children[i - (m + 1) / 2] = node->children[i];

    // 父结点处理
    int pos = __SimpleInsert(node->parent, node->key[(m + 1) / 2]); // 中间关键字上插进父结点
    // 新结点插入父结点子树正确位置
    for (int i = parent->n; i > pos; i--)
        parent->children[i] = parent->children[i - 1];
    parent->children[pos] = newNode;

    // 原结点处理
    node->n = (m - 1) / 2;                 // 修改n
    for (int i = (m + 1) / 2; i <= m; i++) // children无效子树置为NULL
        node->children[i] = NULL;

    if (parent->n == m) // 父结点满判断
        return false;
    else
        return true;
}