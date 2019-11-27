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

BTree NewTree(BTNode *parentNode, int m); // 创建新树，需提供阶数m
bool Search(BTree t, KeyType key); // 搜索

void __Insert(BTree &node, KeyType key, int m);  // 综合插入，指定需插入结点，提供阶数m
int __SimpleInsert(BTNode *node, KeyType key);   // 简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
void __OrderedInsert(BTNode *node, KeyType key); // 顺序插入，仅在确保输入有序时使用
bool __Split(BTNode *node);                      // 分裂，仅在非根结点分裂时使用
void __RootSplit(BTree &root);                   // 根分裂，修改指针

BTree NewTree(BTNode *parentNode, int m)
{
    BTree node = (BTree)malloc(sizeof(BTNode));
    node->n = 0;
    node->parent = parentNode;
    node->key = (KeyType *)calloc(m + 1, sizeof(KeyType));
    node->children = (BTree *)calloc(m + 1, sizeof(BTree));

    return node;
}

bool Search(BTree t, KeyType key)
{
    BTree node = t;
    while (node != NULL)
    {
        int i = 1;
        for (i = 1; node->key[i] < key && i < node->n; i++) // 找到不小于key的最大值
            ;
        if (node->key[i] == key)
            return true;
        else if (node->key[i] < key)
            i++;
        node = node->children[i - 1];
    }
    return false;
}

void __Insert(BTree &node, KeyType key, int m) // 综合插入，指定需插入结点，提供阶数m
{
    __SimpleInsert(node, key); // 先简单插入

    while (node->n == m && node->parent != NULL) // 需分裂且不为根结点
    {
        node = node->parent;
        __Split(node);
    }

    if (node->n == m && node->parent == NULL) // 分裂根结点
        __RootSplit(node);
}

int __SimpleInsert(BTNode *node, KeyType key) // 简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
{
    node->n++;
    // 按顺序插入
    int i;
    for (i = 1; i < node->n; i++)
        if (node->key[i] > key)
            break;

    for (int j = node->n; j > i; j--)
        node->key[j] = node->key[j - 1];
    node->key[i] = key;

    return i;
}

void __OrderedInsert(BTNode *node, KeyType key) // 顺序插入，仅在确保输入有序时使用
{
    node->n++;

    node->key[node->n] = key;
}

bool __Split(BTNode *node) // 分裂，仅在非根结点分裂时使用
{
    int m = node->n;
    BTree parent = node->parent;

    // 新结点处理
    BTree newNode = NewTree(parent, m);    // 新结点
    for (int i = (m + 3) / 2; i <= m; i++) // 插入所有关键字
        __OrderedInsert(newNode, node->key[i]);
    for (int i = (m + 1) / 2; i <= m; i++) // 插入所有子树
        newNode->children[i - (m + 1) / 2] = node->children[i];

    // 父结点处理
    int pos = __SimpleInsert(parent, node->key[(m + 1) / 2]); // 中间关键字上插进父结点
    // 新结点插入父结点子树正确位置
    for (int i = parent->n; i > pos; i--)
        parent->children[i] = parent->children[i - 1];
    parent->children[pos] = newNode;
    parent->children[pos - 1] = node; // 原结点位置

    // 原结点处理
    node->n = (m - 1) / 2;                 // 修改n
    for (int i = (m + 1) / 2; i <= m; i++) // children无效子树置为NULL
        node->children[i] = NULL;

    if (parent->n == m) // 父结点满判断
        return false;
    else
        return true;
}

void __RootSplit(BTree &root) // 根分裂，修改指针
{
    root->parent = NewTree(NULL, root->n);
    __Split(root);
    root = root->parent;
}