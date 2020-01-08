#include <cstdlib>
#include "BT.h"

using namespace std;

BTree BT::NewTree(BTNode *parentNode, int m)
{
    BTree node = (BTree)malloc(sizeof(BTNode));
    node->parent = parentNode;
    node->key = (KeyType *)calloc(m + 1, sizeof(KeyType));
    node->key[0] = 0;
    node->children = (BTree *)calloc(m + 1, sizeof(BTree));

    return node;
}

bool BT::Search(BTree t, KeyType key)
{
    BTree p;
    return BT::__Search(t, key, p);
}

bool BT::Insert(BTree &t, KeyType key, int m)
{
    BTree pos;
    if (BT::isEmpty(t))
    {
        __Insert_Ordered(t, key);
        return true;
    }
    else if (BT::__Search(t, key, pos))
        return false;
    else
    {
        BT::__Insert(pos, key, m, t);
        return true;
    }
}

bool BT::Delete(BTree &t, KeyType key, int m) // ɾ����㣬�Ȳ��ң����������򷵻�false������ɾ��������true
{
    BTNode *p;
    if (BT::__Search(t, key, p))
    {
        if (p->children[0])
            BT::__Delete_NotTerminal(p, key, m, t);
        else
            BT::__Delete_Terminal(p, key, m, t);

        return true;
    }
    else
        return false;
}

void BT::Traverse(BTree t, void Visit(KeyType)) // ����������ݹ飩
{
    if (t)
    {
        BT::Traverse(t->children[0], Visit);
        for (int i = 1; i <= t->key[0]; i++)
        {
            Visit(t->key[i]);
            BT::Traverse(t->children[i], Visit);
        }
    }
}

bool BT::isEmpty(BTree t)
{
    return !t->key[0];
}

void BT::__Insert(BTree &node, KeyType key, int m, BTree &root) // �ۺϲ��룬ָ��������㣬�ṩ����m���ṩroot
{
    BT::__Insert_Simple(node, key); // �ȼ򵥲���

    while (node->key[0] == m && node->parent != NULL) // ������Ҳ�Ϊ�����
    {
        BT::__Split(node);
        node = node->parent;
    }

    if (node->key[0] == m && node->parent == NULL) // ���Ѹ����
        BT::__Split_Root(root);
}

int BT::__Insert_Simple(BTNode *node, KeyType key) // �򵥲��룬���벻��֤���򣬽����������ѣ��ɵ����������жϣ�����ֵΪ����λ��
{
    node->key[0]++;
    // ��˳�����
    int i;
    for (i = 1; node->key[i] < key && i < node->key[0]; i++) // �ҵ���С��key�����ֵ
        ;

    for (int j = node->key[0]; j > i; j--)
        node->key[j] = node->key[j - 1];
    node->key[i] = key;

    return i;
}

void BT::__Insert_Ordered(BTNode *node, KeyType key) // ˳����룬����ȷ����������ʱʹ��
{
    node->key[0]++;

    node->key[node->key[0]] = key;
}

bool BT::__Split(BTNode *node) // ���ѣ����ڷǸ�������ʱʹ��
{
    int m = node->key[0];
    BTree parent = node->parent;

    // �½�㴦��
    BTree newNode = BT::NewTree(parent, m); // �½��
    for (int i = (m + 3) / 2; i <= m; i++)  // �������йؼ���
        BT::__Insert_Ordered(newNode, node->key[i]);
    for (int i = (m + 1) / 2; i <= m; i++) // ���������������޸���parent
    {
        newNode->children[i - (m + 1) / 2] = node->children[i];
        if (newNode->children[i - (m + 1) / 2])
            newNode->children[i - (m + 1) / 2]->parent = newNode;
    }

    // ����㴦��
    int pos = BT::__Insert_Simple(parent, node->key[(m + 1) / 2]); // �м�ؼ����ϲ�������
    // �½����븸���������ȷλ��
    for (int i = parent->key[0]; i > pos; i--)
        parent->children[i] = parent->children[i - 1];
    parent->children[pos] = newNode;
    parent->children[pos - 1] = node; // ԭ���λ��

    // ԭ��㴦��
    node->key[0] = (m - 1) / 2;            // �޸�n
    for (int i = (m + 1) / 2; i <= m; i++) // children��Ч������ΪNULL
        node->children[i] = NULL;

    if (parent->key[0] == m) // ��������ж�
        return false;
    else
        return true;
}

void BT::__Split_Root(BTree &root) // �����ѣ��޸�ָ��
{
    root->parent = BT::NewTree(NULL, root->key[0]);
    BT::__Split(root);
    root = root->parent;
}

bool BT::__Search(BTree t, KeyType key, BTree &pos) // �ڲ����������ҵ��������ڽ�㣬�Ҳ�������Ҫ����Ľ��ָ��
{
    BTree node = t;
    while (true)
    {
        int i = 1;
        for (i = 1; node->key[i] < key && i < node->key[0]; i++) // �ҵ���С��key�����ֵ
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

void BT::__Delete_Simple(BTNode *node, KeyType key) // ��ɾ�����ṩĿ��ڵ㼰Ŀ��key��ɾ�����κδ���
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

void BT::__Delete_NotTerminal(BTNode *node, KeyType key, int m, BTree &t) // ���ն˽��ɾ��
{
    int pos = 1;
    for (pos; node->key[pos] != key; pos++)
        ;

    BTNode *next = node->children[pos];
    for (next; next->children[0]; next = next->children[0])
        ;

    node->key[pos] = next->key[1];
    BT::__Delete_Terminal(next, next->key[1], m, t);
}

void BT::__Delete_Terminal(BTNode *node, KeyType key, int m, BTree &t) // �ն˽��ɾ��
{
    if (node->key[0] >= (m + 1) / 2)
        BT::__Delete_Simple(node, key);
    else if (node->key[0] == (m + 1) / 2 - 1)
    {
        BTNode *parent = node->parent;
        if (!parent)
        {
            BT::__Delete_Root(t, key);
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
        if (posInParent < parent->key[0] && rb->key[0] > (m + 1) / 2 - 1) // ��brother to parent
        {
            node->key[posToDelete] = parent->key[posInParent + 1];
            parent->key[posInParent + 1] = rb->key[1];
            BT::__Delete_Simple(rb, rb->key[1]);
        }
        else if (posInParent > 0 && lb->key[0] > (m + 1) / 2 - 1) // ��brother to parent
        {
            node->key[posToDelete] = parent->key[posInParent];
            parent->key[posInParent] = lb->key[lb->key[0]];
            BT::__Delete_Simple(lb, lb->key[lb->key[0]]);
        }
        else if (posInParent > 0) // parent to ��
        {
            BT::__Delete_Simple(node, key);

            int toAdd = node->key[0] + 1;

            lb->key[lb->key[0] + 1] = parent->key[posInParent];

            for (toAdd; toAdd > 1; toAdd--)
            {
                lb->key[lb->key[0] + toAdd] = node->key[toAdd - 1];
                lb->children[lb->key[0] + toAdd] = node->children[toAdd - 1];
                if (node->children[toAdd - 1])
                    node->children[toAdd - 1]->parent = lb;
            }
            lb->children[lb->key[0] + 1] = node->children[0];
            lb->key[0] += toAdd;

            free(node);
            parent->children[posInParent] = NULL;

            BT::__Delete_Terminal(parent, parent->key[posInParent], m, t);
        }
        else // parent to ��
        {
            BT::__Delete_Simple(node, key);

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
                if (node->children[toAdd - 1])
                    node->children[toAdd - 1]->parent = rb;
            }
            rb->children[0] = node->children[0];

            free(node);
            parent->children[posInParent + 1] = NULL;
            parent->children[posInParent] = rb;

            BT::__Delete_Terminal(parent, parent->key[posInParent + 1], m, t);
        }
    }
}

void BT::__Delete_Root(BTree &t, KeyType key) // �����ɾ��
{
    if (t->key[0] > 1)
        BT::__Delete_Simple(t, key);
    else if (t->children[0])
        t = t->children[0];
    else if (t->children[1])
        t = t->children[1];
    else
        t->key[0]--;

    t->parent = NULL;
}
