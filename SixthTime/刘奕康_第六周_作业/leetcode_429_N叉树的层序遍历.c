/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/n-ary-tree-level-order-traversal/
 *
 * 给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。
 *
 * 树的序列化输入是用层序遍历，每组子节点都由 null 值分隔（参见示例）。
 *
 * 示例
 * 输入：root = [1,null,3,2,4,null,5,6]
 * 输出：[[1],[3,2,4],[5,6]]
 *
 * 输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * 输出：[[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
 *
 * 提示：
 * 树的高度不会超过 1000
 * 树的节点总数在 [0, 10^4] 之间
***/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
    int val;
    int numChildren;
    struct Node** children;
};

//以下为自定义队列，用于层序遍历

typedef struct Node* QueueDataType;

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


//以下MaxDepth方法，获取二叉树深度，节约malloc申请的空间。

int Max(int a, int b)
{
    return a > b ? a : b;
}

int MaxDepth(struct Node* root)
{
    if (root == NULL) {
        return 0;
    }

    int maxDepth = 0;

    for (int i = 0; i < root->numChildren; ++i) {
        maxDepth = Max(maxDepth, MaxDepth(root->children[i]));
    }

    return maxDepth + 1;
}


int** LevelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
    int depth = MaxDepth(root);
    int **res = malloc(sizeof(int *) * depth);
    if (NULL == res) {
        perror("malloc fail\n");
        return NULL;
    }

    *returnColumnSizes = malloc(sizeof(int) * depth);
    if (NULL == *returnColumnSizes) {
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
            if (NULL == curRes) {
                perror("malloc fail\n");
                return NULL;
            }

            for (int i = 0; i < size; i++) {
                struct Node *tmpNode = QueueFront(que);
                curRes[i] = tmpNode->val;
                Pop(que);

                for (int i = 0; i < tmpNode->numChildren; ++i) {
                    if (tmpNode->children[i] != NULL) {
                        Push(que, tmpNode->children[i]);
                    }
                }
            }
            res[curDepth] = curRes;
            ++curDepth;
        }
    }
    FreeQueue(que);

    return res;
}