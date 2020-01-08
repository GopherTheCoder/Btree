#pragma once

typedef int KeyType;
typedef struct BTNode
{
    struct BTNode *parent;
    KeyType *key;
    struct BTNode **children;
} BTNode, *BTree;

class BT
{
public:
    static BTree NewTree(BTNode *parentNode, int m);    // 创建新树，需提供阶数m
    static bool Search(BTree t, KeyType key);           // 搜索
    static bool Insert(BTree &t, KeyType key, int m);   // 添加结点，先查找，若已存在则返回false，否则插入并返回true，需提供阶数m
    static bool Delete(BTree &t, KeyType key, int m);   // 删除结点，先查找，若不存在则返回false，否则删除并返回true
    static void Traverse(BTree t, void Visit(KeyType)); // 升序遍历（递归）
    static bool isEmpty(BTree t);                       // 判断是否为空
private:
    static void __Insert(BTree &node, KeyType key, int m, BTree &root);           // 综合插入，指定需插入结点，提供阶数m，提供root
    static int __Insert_Simple(BTNode *node, KeyType key);                        // 简单插入，输入不保证有序，结果可能需分裂，由调用者自行判断，返回值为插入位置
    static void __Insert_Ordered(BTNode *node, KeyType key);                      // 顺序插入，仅在确保输入有序时使用
    static bool __Split(BTNode *node);                                            // 分裂，仅在非根结点分裂时使用
    static void __Split_Root(BTree &root);                                        // 根分裂，修改指针
    static bool __Search(BTree t, KeyType key, BTree &pos);                       // 内部用搜索，找到返回所在结点，找不到则返回要插入的结点指针
    static void __Delete_Simple(BTNode *node, KeyType key);                       // 简单删除，提供目标节点及目标key，删后不做任何处理
    static void __Delete_NotTerminal(BTNode *node, KeyType key, int m, BTree &t); // 非终端结点删除
    static void __Delete_Terminal(BTNode *node, KeyType key, int m, BTree &t);    // 终端结点删除
    static void __Delete_Root(BTree &t, KeyType key);                             // 根结点删除
};
