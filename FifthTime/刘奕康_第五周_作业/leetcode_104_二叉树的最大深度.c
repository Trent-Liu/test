/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/maximum-depth-of-binary-tree/
 *
 * 给定一个二叉树，找出其最大深度。
 *
 * 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
 *
 * 说明: 叶子节点是指没有子节点的节点。
 *
 * 示例
 * 给定二叉树 [3,9,20,null,null,15,7]，
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * 返回它的最大深度 3 。
 *
***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

//以下为递归方式

//int Max(int a, int b)
//{
//    return a > b ? a : b;
//}
//
//int MaxDepth(struct TreeNode* root)
//{
//    if (root == NULL) {
//        return 0;
//    }
//    return Max(MaxDepth(root->left), MaxDepth(root->right)) + 1;
//}


//以下为层序遍历方式

//首先自定义一个队列
typedef struct TreeNode* QueueDataType;

typedef struct QueueNode
{
    struct QueueNode* next;
    QueueDataType data;
}QueueNode;

typedef struct Queue
{
    QueueNode* head;
    QueueNode* tail;
    int size;
}Queue;


// 初始化队列
Queue* InitQueue()
{

    Queue* q = malloc(sizeof(Queue));
    if (NULL == q)
    {
        perror("malloc fail\n");
        return NULL;
    }
    q->head = q->tail = NULL;
    q->size = 0;

    return q;
}


// 销毁队列
void FreeQueue(Queue* q)
{
    assert(q);

    //释放结点
    while (q->head)
    {
        QueueNode* next = q->head->next;
        if (q->tail != q->head)
        {
            free(q->head);
            q->head = next;
        }
        else
        {
            //避免野指针
            free(q->head);
            q->head=q->tail = NULL;
        }
    }
    //手动置零
    q->size = 0;
    free(q);
}


// 检测队列是否为空，如果为空返回非零结果，如果非空返回0
int IsQueueEmpty(Queue* q)
{
    assert(q);

    return q->size == 0;
}


// 队尾入队列
void Push(Queue* q, QueueDataType data)
{
    //断言判断指针有效性
    assert(q);

    //开辟结点
    QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
    if (NULL == newnode)
    {
        perror("malloc fail\n");
        return;
    }
    newnode->next = NULL;
    newnode->data = data;


    //插入数据
    //空队列插入数据
    if (q->head == NULL)
    {
        q->head = q->tail = newnode;
    }
        //非空队列插入数据
    else
    {
        q->tail->next = newnode;
        q->tail = newnode;
    }

    q->size++;
}

// 队头出队列
void Pop(Queue* q)
{
    assert(q);
    //空队列无法删除数据
    assert(!IsQueueEmpty(q));


    //只有一个数据
    if (q->head == q->tail)
    {
        free(q->head);
        q->head = q->tail = NULL;
    }
    else
    {
        //先保存下一个结点
        QueueNode* next = q->head->next;
        free(q->head);
        q->head = next;
    }

    //记录当前数据个数
    q->size--;

}

// 获取队列中有效元素个数
int QueueSize(Queue* q)
{
    assert(q);

    return q->size;
}

// 获取队列头部元素
QueueDataType QueueFront(Queue* q)
{
    assert(q);
    assert(!IsQueueEmpty(q));

    return q->head->data;
}

// 获取队列队尾元素
QueueDataType QueueBack(Queue* q)
{
    assert(q);
    assert(!IsQueueEmpty(q));

    return q->tail->data;

}

//层序遍历做法
int MaxDepth(struct TreeNode* root)
{
    int deepth = 0;
    Queue *que = InitQueue();

    if (root != NULL) {
        Push(que, root);
        while (!IsQueueEmpty(que)) {
            int size = QueueSize(que);
            deepth++;
            for (int i = 0; i < size; i++) {
                struct TreeNode* tmpNode = QueueFront(que);
                Pop(que);
                if (tmpNode -> left) {
                    Push(que, tmpNode -> left);
                }
                if (tmpNode -> right) {
                    Push(que, tmpNode -> right);
                }
            }
        }
    }
    FreeQueue(que);
    return deepth;
}