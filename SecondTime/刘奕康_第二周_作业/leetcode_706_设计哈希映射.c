/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/design-hashmap/
 *
 * 不使用任何内建的哈希表库设计一个哈希映射（HashMap）。
 *
 * 实现 MyHashMap 类：

 * MyHashMap() 用空映射初始化对象
 * void put(int key, int value) 向 HashMap 插入一个键值对 (key, value) 。如果 key 已经存在于映射中，则更新其对应的值 value 。
 * int get(int key) 返回特定的 key 所映射的 value ；如果映射中不包含 key 的映射，返回 -1 。
 * void remove(key) 如果映射中存在 key 的映射，则移除 key 和它所对应的 value 。
 *
 * 示例
 * 输入：
 * ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
 * [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
 * 输出：
 * [null, null, null, 1, -1, null, 1, null, -1]
 *
 * 解释：
 * MyHashMap myHashMap = new MyHashMap();
 * myHashMap.put(1, 1); // myHashMap 现在为 [[1,1]]
 * myHashMap.put(2, 2); // myHashMap 现在为 [[1,1], [2,2]]
 * myHashMap.get(1);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,2]]
 * myHashMap.get(3);    // 返回 -1（未找到），myHashMap 现在为 [[1,1], [2,2]]
 * myHashMap.put(2, 1); // myHashMap 现在为 [[1,1], [2,1]]（更新已有的值）
 * myHashMap.get(2);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,1]]
 * myHashMap.remove(2); // 删除键为 2 的数据，myHashMap 现在为 [[1,1]]
 * myHashMap.get(2);    // 返回 -1（未找到），myHashMap 现在为 [[1,1]]
 *
 * 提示：
 * 0 <= key, value <= 106
 * 最多调用 104 次 put、get 和 remove 方法
***/
#include<stdlib.h>

#define HASHLEN 997

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
    struct List *tmp = (struct List*)malloc(sizeof(struct List));
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
        struct List* tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

int CalHash(int key) {
    return key % HASHLEN;
}


MyHashMap* MyHashMapCreate()
{
    MyHashMap *hashMap = (MyHashMap*)malloc(sizeof(MyHashMap));
    if (hashMap == NULL) {
        return NULL;
    }
    hashMap->list = (struct List*)malloc(sizeof(struct List) * HASHLEN);
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

void MyHashMapPut(MyHashMap* obj, int key, int value)
{
    int hash = CalHash(key);
    struct List *hashNode = ListFind(&(obj->list[hash]), key);
    if (hashNode == NULL) {
        ListPush(&(obj->list[hash]), key, value);
    } else {
        hashNode->val = value;
    }
}

int myHashMapGet(MyHashMap* obj, int key) {
    int hash = CalHash(key);
    struct List* hashNode = ListFind(&(obj->list[hash]), key);
    if (hashNode == NULL) {
        return -1;
    } else {
        return hashNode->val;
    }
}

void MyHashMapRemove(MyHashMap* obj, int key)
{
    int hash = CalHash(key);
    ListDelete(&(obj->list[hash]), key);
}

void MyHashMapFree(MyHashMap* obj)
{
    for (int i = 0; i < HASHLEN; ++i) {
        ListFree(&(obj->list[i]));
    }
    free(obj->list);
}
