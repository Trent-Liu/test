/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/maximum-width-of-binary-tree/
 *
 * 给你一棵二叉树的根节点 root ，返回树的 最大宽度 。
 *
 * 树的 最大宽度 是所有层中最大的 宽度 。
 *
 * 每一层的 宽度 被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。将这个二叉树视作与满二叉树结构相同，两端点间会出现一些延伸到这一层的 null 节点，这些 null 节点也计入长度。
 *
 * 题目数据保证答案将会在  32 位 带符号整数范围内。
 *
 * 示例
 * 输入：root = [1,3,2,5,3,null,9]
 * 输出：4
 * 解释：最大宽度出现在树的第 3 层，宽度为 4 (5,3,null,9) 。
 *
 * 输入：root = [1,3,2,5,null,null,9,6,null,7]
 * 输出：7
 * 解释：最大宽度出现在树的第 4 层，宽度为 7 (6,null,null,null,null,null,7) 。
 *
 * 输入：root = [1,3,2,5]
 * 输出：2
 * 解释：最大宽度出现在树的第 2 层，宽度为 2 (3,2) 。
 *
 * 提示：
 * 树中节点的数目范围是 [1, 3000]
 * -100 <= Node.val <= 100
***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNodeMsg {
    struct TreeNode *node;
    unsigned long long val;
};

typedef struct TreeNodeMsg* QueueDataType;

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

unsigned long long MaxLong(unsigned long long a, unsigned long long b)
{
    return a > b ? a : b;
}


int WidthOfBinaryTree(struct TreeNode* root)
{
    unsigned long long res = 0;

    Queue *que = InitQueue();
    if (root == NULL) {
        return 0;
    }

    struct TreeNodeMsg *rootMsg = malloc(sizeof(struct TreeNodeMsg));
    if (NULL == rootMsg) {
        perror("malloc fail\n");
        return 0;
    }
    rootMsg->node = root;
    rootMsg->val = 1L;

    Push(que, rootMsg);
    while (!IsQueueEmpty(que)) {

        int size = QueueSize(que);

        res = MaxLong(res, QueueBack(que)->val - QueueFront(que)->val + 1);

        for (int i = 0; i < size; i++) {
            struct TreeNodeMsg *tmpNodeMsg = QueueFront(que);
            struct TreeNode *tmpNode = tmpNodeMsg->node;
            unsigned long long index = tmpNodeMsg->val;

            Pop(que);
            if (tmpNode->left != NULL) {
                struct TreeNodeMsg *node = malloc(sizeof(struct TreeNodeMsg));
                if (NULL == node) {
                    perror("malloc fail\n");
                    return 0;
                }
                node->node = tmpNode->left;
                node->val = index * 2;
                Push(que, node);
            }
            if (tmpNode->right != NULL) {
                struct TreeNodeMsg *node = malloc(sizeof(struct TreeNodeMsg));
                if (NULL == node) {
                    perror("malloc fail\n");
                    return 0;
                }
                node->node = tmpNode->right;
                node->val = index * 2 + 1;
                Push(que, node);
            }

            free(tmpNode);
        }
    }
    FreeQueue(que);

    return (int)res;
}