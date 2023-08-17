自定义哈希表

```C
#define HASHLEN 9973

struct List {
    int key;
    int val;
    struct List *next;
};


typedef struct {
    struct List *list;
} MyHashMap;


// 头插
void ListPush(struct List *head, int key, int val)
{
    struct List *tmp = malloc(sizeof(struct List));
    if (tmp == NULL) {
        return;
    }
    tmp->key = key;
    tmp->val = val;
    tmp->next = head->next;
    head->next = tmp;
}

void ListDelete(struct List *head, int key)
{
    struct List *it = head;
    while (it->next) {
        if (it->next->key == key) {
            struct List *tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
        it = it->next;
    }
}

struct List* ListFind(struct List *head, int key)
{
    if (key < 0) {
        return NULL;
    }
    struct List *it = head;
    while (it->next) {
        if (it->next->key == key) {
            return it->next;
        }
        it = it->next;
    }
    return NULL;
}

void ListFree(struct List* head)
{
    while (head->next) {
        struct List *tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

int CalHash(int key) {
    return key % HASHLEN;
}


//创建哈希表
MyHashMap* MyHashMapCreate()
{
    MyHashMap *hashMap = malloc(sizeof(MyHashMap));
    if (hashMap == NULL) {
        return NULL;
    }
    hashMap->list = malloc(sizeof(struct List) * HASHLEN);
    if (hashMap->list == NULL) {
        return NULL;
    }
    for (int i = 0; i < HASHLEN; ++i) {
        hashMap->list[i].key = 0;
        hashMap->list[i].val = 0;
        hashMap->list[i].next = NULL;
    }
    return hashMap;
}

//存放元素
void MyHashMapPut(MyHashMap* obj, int key, int value)
{
    key = key + 10000000;
    int hash = CalHash(key);
    struct List *hashNode = ListFind(&(obj->list[hash]), key);
    if (hashNode == NULL) {
        ListPush(&(obj->list[hash]), key, value);
    } else {
        hashNode->val = value;
    }
}

//获取
int MyHashMapGet(MyHashMap* obj, int key) {
    key = key + 10000000;
    int hash = CalHash(key);
    struct List *hashNode = ListFind(&(obj->list[hash]), key);
    if (hashNode == NULL) {
        return -1;
    } else {
        return hashNode->val;
    }
}

//删除元素
void MyHashMapRemove(MyHashMap* obj, int key)
{
    int hash = CalHash(key);
    ListDelete(&(obj->list[hash]), key);
}

//释放哈希表
void MyHashMapFree(MyHashMap* obj)
{
    for (int i = 0; i < HASHLEN; ++i) {
        ListFree(&(obj->list[i]));
    }
    free(obj->list);
}

```


C语言自带哈希表

```C
typedef struct hash {
    int key;
    int val;
    UT_hash_handle hh;
} hash_table;


hash_table *hp = NULL;
hash_table *p = NULL;

//向哈希表中存放元素
    p = malloc(sizeof(hash_table));

    p->key = 0;
    p->val = 1;

    HASH_ADD_INT(hp, key, p);

	//获取，得不到的话为NULL
	HASH_FIND_INT(hp, &cur, p);
    if (p == NULL) {
    }


struct HashNode {
    int val;
    int count;
    UT_hash_handle hh;
};

int CmpCount(const struct HashNode *a, const struct HashNode *b)
{
    if (a->count == b->count) {
        return b->val = a->val;
    } else {
        return a->count - b->count;
    }
}
 HASH_SORT(mp, CmpCount);

    int i = 0;
    for (hashTmp = mp; hashTmp != NULL; hashTmp = hashTmp->hh.next) {
        while(hashTmp->count--) {
            nums[i++] = hashTmp->val;
        }
    }

    struct HashNode *cur, *tmp;
    HASH_ITER(hh, mp, cur, tmp) {
        HASH_DEL(mp, cur);
        free(cur);
    }


```



栈
```C

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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


```




快排
```C
#include <stdlib.h>
#include <time.h>

void Swap(int* nums, int index1, int index2)
{
    int tmp = nums[index1];
    nums[index1] = nums[index2];
    nums[index2] = tmp;
    return;
}

int Partition(int* nums, int left, int right)
{
    int ran = left + rand()%(right - left + 1);
    Swap(nums, ran, left);
    int base = nums[left];

    while (left < right) {
        while (left < right && nums[right] >= base) {
            --right;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] < base) {
            ++left;
        }
        nums[right] = nums[left];
    }
    nums[left] = base;
    return left;
}

void QuickSort(int* nums, int left, int right)
{
    if (left >= right) {
        return;
    }
    int base = Partition(nums, left, right);
    QuickSort(nums, left, base - 1);
    QuickSort(nums, base + 1, right);
}

int MaxProduct(int* nums, int numsSize)
{
    srand((int)time(0));
    QuickSort(nums, 0, numsSize-1);

    return (nums[numsSize - 1] - 1) * (nums[numsSize - 2] - 1);
}
```



堆排

```C
void Swap(int* nums, int index1, int index2)
{
    int tmp = nums[index1];
    nums[index1] = nums[index2];
    nums[index2] = tmp;
    return;
}

void MaxHeapify(int* nums, int i, int len)
{
    for (i; (i * 2) + 1 <= len;) {
        int lson = i * 2 + 1;
        int rson = i * 2 + 2;
        int large = i;
        if (lson <= len && nums[lson] > nums[large]) {
            large = lson;
        }
        if (rson <= len && nums[rson] > nums[large]) {
            large = rson;
        }
        if (large != i) {
            Swap(nums, i, large);
            i = large;
        } else {
            break;
        }
    }
}


void HeapSort(int* nums, int numsSize)
{
    int len = numsSize - 1;
    for (int i = len/2; i >= 0; --i) {
        MaxHeapify(nums, i, len);
    }
    for (int i = len; i >= 1; --i) {
        Swap(nums, i, 0);
        len -= 1;
        MaxHeapify(nums, 0, len);
    }
}

int* SortArray(int* nums, int numsSize, int* returnSize)
{
    *returnSize = numsSize;

    HeapSort(nums, numsSize);

    return nums;
}

···





队列

```C
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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

```



层序遍历

```C
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
```

通用的二叉树遍历

```C
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
```