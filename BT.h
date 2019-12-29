#pragma once
#include <cstdlib>
//#include "Graphviz.h"

using namespace std;

typedef int KeyType;
typedef struct BTNode
{
    struct BTNode *parent;
    KeyType *key;
    struct BTNode **children;
} BTNode, *BTree;

BTree NewTree(BTNode *parentNode, int m);    // 创建新树，需提供阶数m
bool Search(BTree t, KeyType key);           // 搜索
bool Insert(BTree &t, KeyType key, int m);   // 添加结点，先查找，若已存在则返回false，否则插入并返回true，需提供阶数m
bool Delete(BTree &t, KeyType key, int m);   // 删除结点，先查找，若不存在则返回false，否则删除并返回true
void Traverse(BTree t, void Visit(KeyType)); // 升序遍历（递归）

void __Insert(BTree &node, KeyType key, int m, BTree &root);           // 综合插入，指定需插入结点，提供阶数m，提供root
int __Insert_Simple(BTNode *node, KeyType key);                        // 简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
void __Insert_Ordered(BTNode *node, KeyType key);                      // 顺序插入，仅在确保输入有序时使用
bool __Split(BTNode *node);                                            // 分裂，仅在非根结点分裂时使用
void __Split_Root(BTree &root);                                        // 根分裂，修改指针
bool __Search(BTree t, KeyType key, BTree &pos);                       // 内部用搜索，找到返回所在结点，找不到则返回要插入的结点指针
void __Delete_Simple(BTNode *node, KeyType key);                       // 简单删除，提供目标节点及目标key，删后不做任何处理
void __Delete_NotTerminal(BTNode *node, KeyType key, int m, BTree &t); // 非终端结点删除
void __Delete_Terminal(BTNode *node, KeyType key, int m, BTree &t);    // 终端结点删除
void __Delete_Root(BTree &t, KeyType key);                             // 根结点删除

BTree NewTree(BTNode *parentNode, int m)
{
    BTree node = (BTree)malloc(sizeof(BTNode));
    node->parent = parentNode;
    node->key = (KeyType *)calloc(m + 1, sizeof(KeyType));
    node->key[0] = 0;
    node->children = (BTree *)calloc(m + 1, sizeof(BTree));

    return node;
}

bool Search(BTree t, KeyType key)
{
    BTree p;
    return __Search(t, key, p);
}

bool Insert(BTree &t, KeyType key, int m)
{
    BTree pos;
    if (__Search(t, key, pos))
        return false;
    else
    {
        __Insert(pos, key, m, t);
        return true;
    }
}

bool Delete(BTree &t, KeyType key, int m) // 删除结点，先查找，若不存在则返回false，否则删除并返回true
{
    BTNode *p;
    if (__Search(t, key, p))
    {
        if (p->children[0])
            __Delete_NotTerminal(p, key, m, t);
        else
            __Delete_Terminal(p, key, m, t);

        return true;
    }
    else
        return false;
}

void Traverse(BTree t, void Visit(KeyType)) // 升序遍历（递归）
{
    if (t)
    {
        Traverse(t->children[0], Visit);
        for (int i = 1; i <= t->key[0]; i++)
        {
            Visit(t->key[i]);
            Traverse(t->children[i], Visit);
        }
    }
}

void __Insert(BTree &node, KeyType key, int m, BTree &root) // 综合插入，指定需插入结点，提供阶数m，提供root
{
    __Insert_Simple(node, key); // 先简单插入

    while (node->key[0] == m && node->parent != NULL) // 需分裂且不为根结点
    {
        __Split(node);
        node = node->parent;
    }

    if (node->key[0] == m && node->parent == NULL) // 分裂根结点
        __Split_Root(root);
}

int __Insert_Simple(BTNode *node, KeyType key) // 简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
{
    node->key[0]++;
    // 按顺序插入
    int i;
    for (i = 1; i < node->key[0]; i++)
        if (node->key[i] > key)
            break;

    for (int j = node->key[0]; j > i; j--)
        node->key[j] = node->key[j - 1];
    node->key[i] = key;

    return i;
}

void __Insert_Ordered(BTNode *node, KeyType key) // 顺序插入，仅在确保输入有序时使用
{
    node->key[0]++;

    node->key[node->key[0]] = key;
}

bool __Split(BTNode *node) // 分裂，仅在非根结点分裂时使用
{
    int m = node->key[0];
    BTree parent = node->parent;

    // 新结点处理
    BTree newNode = NewTree(parent, m);    // 新结点
    for (int i = (m + 3) / 2; i <= m; i++) // 插入所有关键字
        __Insert_Ordered(newNode, node->key[i]);
    for (int i = (m + 1) / 2; i <= m; i++) // 插入所有子树并修改其parent
    {
        newNode->children[i - (m + 1) / 2] = node->children[i];
        if (newNode->children[i - (m + 1) / 2])
            newNode->children[i - (m + 1) / 2]->parent = newNode;
    }

    // 父结点处理
    int pos = __Insert_Simple(parent, node->key[(m + 1) / 2]); // 中间关键字上插进父结点
    // 新结点插入父结点子树正确位置
    for (int i = parent->key[0]; i > pos; i--)
        parent->children[i] = parent->children[i - 1];
    parent->children[pos] = newNode;
    parent->children[pos - 1] = node; // 原结点位置

    // 原结点处理
    node->key[0] = (m - 1) / 2;            // 修改n
    for (int i = (m + 1) / 2; i <= m; i++) // children无效子树置为NULL
        node->children[i] = NULL;

    if (parent->key[0] == m) // 父结点满判断
        return false;
    else
        return true;
}

void __Split_Root(BTree &root) // 根分裂，修改指针
{
    root->parent = NewTree(NULL, root->key[0]);
    __Split(root);
    root = root->parent;
}

bool __Search(BTree t, KeyType key, BTree &pos) // 内部用搜索，找到返回所在结点，找不到返回要插入的结点指针
{
    BTree node = t;
    while (true)
    {
        int i = 1;
        for (i = 1; node->key[i] < key && i < node->key[0]; i++) // 找到不小于key的最大值
            ;
        if (node->key[i] == key)
        {
            pos = node;
            return true;
        }
        else if (node->key[i] < key)
            i++;
        if (node->children[i - 1] == NULL)
        {
            pos = node;
            return false;
        }
        node = node->children[i - 1];
    }
}

void __Delete_Simple(BTNode *node, KeyType key) // 简单删除，提供目标节点及目标key，删后不做任何处理
{
    int pos = 1;
    for (pos; node->key[pos] != key; pos++)
        ;

    for (int i = pos + 1; i <= node->key[0]; i++)
    {
        node->key[i - 1] = node->key[i];
        node->children[i - 1] = node->children[i];
    }

    node->key[0]--;
}

void __Delete_NotTerminal(BTNode *node, KeyType key, int m, BTree &t) // 非终端结点删除
{
    int pos = 1;
    for (pos; node->key[pos] != key; pos++)
        ;

    BTNode *next = node->children[pos];
    for (next; next->children[0]; next = next->children[0])
        ;

    node->key[pos] = next->key[1];
    __Delete_Terminal(next, next->key[1], m, t);
}

void __Delete_Terminal(BTNode *node, KeyType key, int m, BTree &t) // 终端结点删除
{
    if (node->key[0] >= (m + 1) / 2)
        __Delete_Simple(node, key);
    else if (node->key[0] == (m + 1) / 2 - 1)
    {
        BTNode *parent = node->parent;
        if (!parent)
        {
            __Delete_Root(t, key);
            return;
        }
        int posToDelete = 1;
        for (posToDelete; node->key[posToDelete] != key; posToDelete++)
            ;
        int posInParent = 0;
        for (posInParent; parent->children[posInParent] != node; posInParent++)
            ;

        BTNode *lb = parent->children[posInParent - 1],
               *rb = parent->children[posInParent + 1];
        if (posInParent < parent->key[0] && rb->key[0] > (m + 1) / 2 - 1) // 右brother to parent
        {
            node->key[posToDelete] = parent->key[posInParent + 1];
            parent->key[posInParent + 1] = rb->key[1];
            __Delete_Simple(rb, rb->key[1]);
        }
        else if (posInParent > 0 && lb->key[0] > (m + 1) / 2 - 1) // 左brother to parent
        {
            node->key[posToDelete] = parent->key[posInParent];
            parent->key[posInParent] = lb->key[lb->key[0]];
            __Delete_Simple(lb, lb->key[lb->key[0]]);
        }
        else if (posInParent > 0) // parent to 左
        {
            __Delete_Simple(node, key);

            int toAdd = node->key[0] + 1;

            lb->key[lb->key[0] + 1] = parent->key[posInParent];

            for (toAdd; toAdd > 1; toAdd--)
            {
                lb->key[lb->key[0] + toAdd] = node->key[toAdd - 1];
                lb->children[lb->key[0] + toAdd] = node->children[toAdd - 1];
            }
            lb->children[lb->key[0] + 1] = node->children[0];
            lb->key[0] += toAdd;

            free(node);
            parent->children[posInParent] = NULL;

            __Delete_Terminal(parent, parent->key[posInParent], m, t);
        }
        else // parent to 右
        {
            __Delete_Simple(node, key);

            int toAdd = node->key[0] + 1;
            for (int i = rb->key[0] + toAdd; i >= toAdd + 1; i--)
            {
                rb->key[i] = rb->key[i - toAdd];
                rb->children[i] = rb->children[i - toAdd];
            }
            rb->children[toAdd] = rb->children[0];
            rb->key[0] += toAdd;

            rb->key[toAdd] = parent->key[posInParent + 1];

            for (toAdd; toAdd > 1; toAdd--)
            {
                rb->key[toAdd - 1] = node->key[toAdd - 1];
                rb->children[toAdd - 1] = node->children[toAdd - 1];
            }
            rb->children[0] = node->children[0];

            free(node);
            parent->children[posInParent + 1] = NULL;
            parent->children[posInParent] = rb;

            __Delete_Terminal(parent, parent->key[posInParent + 1], m, t);
        }
    }
}

void __Delete_Root(BTree &t, KeyType key) // 根结点删除
{
    if (t->key[0] > 1)
        __Delete_Simple(t, key);
    else
        t = t->children[0] ? t->children[0] : t->children[1];
}