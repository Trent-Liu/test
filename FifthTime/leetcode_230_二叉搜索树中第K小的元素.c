/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/kth-smallest-element-in-a-bst/
 *
 * 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。
 *
 * 示例
 * 输入：root = [3,1,4,null,2], k = 1
 * 输出：1
 *
 * 输入：root = [5,3,6,2,4,null,null,1], k = 3
 * 输出：3
 *
 * 提示：
 * 树中的节点数为 n 。
 * 1 <= k <= n <= 104
 * 0 <= Node.val <= 104
 *
***/
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

////递归形式的中序遍历
//void Inorder(struct TreeNode *root, int *res, int *size)
//{
//    if(root == NULL)
//        return;
//    Inorder(root->left, res, size);
//    res[(*size)++] = root->val;
//    Inorder(root->right, res, size);
//}
//
//int KthSmallest(struct TreeNode* root, int k)
//{
//    if(root == NULL)
//        return NULL;
//
//    int* res = malloc(sizeof(int) * 100000);
//    if (NULL == res)
//    {
//        perror("malloc fail\n");
//        return -1;
//    }
//    int *size = malloc(sizeof(int));
//    if (NULL == size)
//    {
//        perror("malloc fail\n");
//        return -1;
//    }
//
//    *size = 0;
//    Inorder(root, res, size);
//    return res[k - 1];
//}


//下面是迭代方式，使用栈的遍历，先中后通用写法

typedef struct TreeNode* StackDataType;

typedef struct Stack {
    StackDataType *data;
    int size, top;
} Stack;

Stack *InitStack(int n)
{
    Stack *st = malloc(sizeof(Stack));
    st->data = malloc(sizeof(StackDataType) * n);
    st->size = n;
    st->top = -1;
    return st;
}

int IsEmpty(Stack *st)
{
    return st->top == -1;
}

StackDataType Top(Stack *st)
{
    return st->data[st->top];
}

int Push(Stack *st, StackDataType data)
{
    if (st == NULL) {
        return 0;
    }
    if (st->top == st->size-1) {
        return 0;
    }
    ++st->top;
    st->data[st->top] = data;

    return 1;
}

int Pop(Stack *st)
{
    if (st == NULL) {
        return 0;
    }
    if (IsEmpty(st)) {
        return 0;
    }
    --st->top;
    return 1;
}

void ClearStack(Stack *st)
{
    if (st == NULL) {
        return;
    }
    free(st->data);
    free(st);
    return;
}


//迭代形式的中序遍历，需要使用栈，先序与后序通用。
int KthSmallest(struct TreeNode* root, int k)
{
    int *res = (int *)malloc(sizeof(int) * 100000);
    if (NULL == res)
    {
        perror("malloc fail\n");
        return -1;
    }
    int *size = (int *)malloc(sizeof(int));
    if (NULL == size)
    {
        perror("malloc fail\n");
        return -1;
    }

    *size = 0;

    if (!root) {
        return res;
    }

    Stack *stack = InitStack(2000);
    Push(stack, root);

    while (!IsEmpty(stack)) {
        struct TreeNode* node = Top(stack);
        Pop(stack);
        if (node != NULL) {
            if (node->right) {
                Push(stack, node->right);
            }
            Push(stack, node);
            Push(stack, NULL);
            if (node->left) {
                Push(stack, node->left);
            }
        } else {
            node = Top(stack);
            Pop(stack);
            res[(*size)++] = node->val;
        }
    }

    int tmp = res[k - 1];

    free(res);
    free(size);
    ClearStack(stack);
    return tmp;
}

