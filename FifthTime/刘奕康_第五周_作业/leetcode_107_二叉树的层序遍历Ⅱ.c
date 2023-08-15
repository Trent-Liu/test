/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/
 *
 * 给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
 *
 * 示例
 * 输入：root = [3,9,20,null,null,15,7]
 * 输出：[[15,7],[9,20],[3]]
 *
 * 输入：root = [1]
 * 输出：[[1]]
 *
 * 输入：root = []
 * 输出：[]
 *
 * 提示：
 * 树中节点数目在范围 [0, 2000] 内
 * -1000 <= Node.val <= 1000
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

//以下为自定义队列，用于层序遍历

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

//以下MaxDepth方法，获取二叉树深度，节约malloc申请的空间。

int Max(int a, int b)
{
    return a > b ? a : b;
}

int MaxDepth(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    return Max(MaxDepth(root->left), MaxDepth(root->right)) + 1;
}

//以下两个revise方法，用于层序遍历后revise最终遍历结果和每层的元素数量

void ReviseRes(int **list, int size)
{
    int i = 0;
    int j = size - 1;
    for (i, j; i < j; ++i, --j) {
        int *tmp = list[i];
        list[i] = list[j];
        list[j] = tmp;
    }
}

void ReviseColumnSizes(int *list, int size)
{
    int i = 0;
    int j = size - 1;
    for (i, j; i < j; ++i, --j) {
        int tmp = list[i];
        list[i] = list[j];
        list[j] = tmp;
    }
}

int** LevelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    int depth = MaxDepth(root);
    int **res = malloc(sizeof(int *) * depth);
    if (NULL == res)
    {
        perror("malloc fail\n");
        return NULL;
    }

    *returnColumnSizes = malloc(sizeof(int) * depth);
    if (NULL == *returnColumnSizes)
    {
        perror("malloc fail\n");
        return NULL;
    }

    *returnSize = depth;

    Queue *que = InitQueue();
    int curDepth = 0;

    if (root != NULL) {
        Push(que, root);
        while (!IsQueueEmpty(que)) {

            int size = QueueSize(que);

            (*returnColumnSizes)[curDepth] = size;

            int *curRes = malloc(sizeof(int) * size);
            if (NULL == curRes)
            {
                perror("malloc fail\n");
                return NULL;
            }

            for (int i = 0; i < size; i++) {
                struct TreeNode *tmpNode = QueueFront(que);
                curRes[i] = tmpNode->val;
                Pop(que);
                if (tmpNode->left) {
                    Push(que, tmpNode->left);
                }
                if (tmpNode->right) {
                    Push(que, tmpNode->right);
                }
            }
            res[curDepth] = curRes;
            ++curDepth;
        }
    }
    FreeQueue(que);
    ReviseRes(res, depth);
    ReviseColumnSizes(*returnColumnSizes, depth);

    return res;
}