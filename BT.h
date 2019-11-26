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

BTree NewTree(BTNode *parentNode, int m)
{
    BTree node = (BTree)malloc(sizeof(BTNode));
    node->n = 0;
    node->parent = parentNode;
    node->key = (KeyType *)calloc(m + 1, sizeof(KeyType));
    node->children = (BTree *)calloc(m + 1, sizeof(BTree));

    return node;
}

int __SimpleInsert(BTNode *node, KeyType key) // �򵥲��룬���벻��֤���򣬽����������ѣ��ɵ����������жϣ�����ֵΪ����λ��
{
    node->n++;
    // ��˳�����
    int i;
    for (i = 1; i < node->n; i++)
        if (node->key[i] > key)
            break;

    for (int j = node->n; j > i; j--)
        node->key[j] = node->key[j - 1];
    node->key[i] = key;

    return i;
}

void __OrderedInsert(BTNode *node, KeyType key) // ˳����룬����ȷ����������ʱʹ��
{
    node->n++;

    node->key[node->n] = key;
}

bool __Split(BTNode *node) // ���ѣ����ڷǸ�������ʱʹ��
{
    int m = node->n;
    BTree parent = node->parent;

    // �½�㴦��
    BTree newNode = NewTree(parent, m);    // �½��
    for (int i = (m + 3) / 2; i <= m; i++) // �������йؼ���
        __OrderedInsert(newNode, node->key[i]);
    for (int i = (m + 1) / 2; i <= m; i++) // ������������
        newNode->children[i - (m + 1) / 2] = node->children[i];

    // ����㴦��
    int pos = __SimpleInsert(parent, node->key[(m + 1) / 2]); // �м�ؼ����ϲ�������
    // �½����븸���������ȷλ��
    for (int i = parent->n; i > pos; i--)
        parent->children[i] = parent->children[i - 1];
    parent->children[pos] = newNode;
    parent->children[pos - 1] = node; // ԭ���λ��

    // ԭ��㴦��
    node->n = (m - 1) / 2;                 // �޸�n
    for (int i = (m + 1) / 2; i <= m; i++) // children��Ч������ΪNULL
        node->children[i] = NULL;

    if (parent->n == m) // ��������ж�
        return false;
    else
        return true;
}

void __RootSplit(BTree root)    // �����ѣ��޸�ָ��
{
    root->parent = NewTree(NULL, root->n);
    __Split(root);
    *root = *(root->parent);
}