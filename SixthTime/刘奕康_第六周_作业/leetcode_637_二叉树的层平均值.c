/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/average-of-levels-in-binary-tree/
 *
 * 给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。
 *
 * 示例
 * 输入：root = [3,9,20,null,null,15,7]
 * 输出：[3.00000,14.50000,11.00000]
 * 解释：第 0 层的平均值为 3,第 1 层的平均值为 14.5,第 2 层的平均值为 11 。
 * 因此返回 [3, 14.5, 11] 。
 *
 * 输入：root = [3,9,20,15,7]
 * 输出：[3.00000,14.50000,11.00000]
 *
 * 提示：
 * 树中节点数量在 [1, 104] 范围内
 * -231 <= Node.val <= 231 - 1
***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode* QueueDataType;

typedef struct QueueNode {
    struct QueueNode* next;
    QueueDataType data;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
    int size;
} Queue;


// 初始化队列
Queue* InitQueue()
{

    Queue* q = malloc(sizeof(Queue));
    if (NULL == q) {
        perror("malloc fail\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}


// 销毁队列
void FreeQueue(Queue* q)
{
    assert(q);

    //释放结点
    while (q->head) {
        QueueNode* next = q->head->next;
        if (q->tail != q->head) {
            free(q->head);
            q->head = next;
        } else {
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
    QueueNode* newNode = malloc(sizeof(QueueNode));
    if (NULL == newNode) {
        perror("malloc fail\n");
        return;
    }
    newNode->next = NULL;
    newNode->data = data;


    //插入数据
    //空队列插入数据
    if (q->head == NULL) {
        q->head = q->tail = newNode;
    } else {
        //非空队列插入数据
        q->tail->next = newNode;
        q->tail = newNode;
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
    if (q->head == q->tail) {
        free(q->head);
        q->head = q->tail = NULL;
    } else {
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


double* AverageOfLevels(struct TreeNode* root, int* returnSize)
{
    int depth = MaxDepth(root);
    double *res = malloc(sizeof(double) * depth);
    if (NULL == res) {
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
            double curSum = 0;

            for (int i = 0; i < size; i++) {
                struct TreeNode *tmpNode = QueueFront(que);
                curSum += tmpNode->val;

                Pop(que);
                if (tmpNode->left) {
                    Push(que, tmpNode->left);
                }
                if (tmpNode->right) {
                    Push(que, tmpNode->right);
                }
            }

            res[curDepth] = curSum / size;
            ++curDepth;
        }
    }
    FreeQueue(que);

    return res;
}