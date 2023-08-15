/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/subarray-sum-equals-k/description/?languageTags=c
 *
 * 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的连续子数组的个数 。
 *
 * 示例
 * 输入：nums = [1,1,1], k = 2
 * 输出：2
 *
 * 输入：nums = [1,2,3], k = 3
 * 输出：2
 *
 * 提示：
 * 1 <= nums.length <= 2 * 104
 * -1000 <= nums[i] <= 1000
 * -107 <= k <= 107
***/

#include<stdlib.h>
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


int SubarraySum(int* nums, int numsSize, int k){
    int pre_num = 0;
    MyHashMap *mp = MyHashMapCreate();
    MyHashMapPut(mp, 0, 1);
    int res = 0;
    for (int i = 1; i <= numsSize; ++i) {
        pre_num = nums[i-1] + pre_num;
        int tmpValue = MyHashMapGet(mp, pre_num - k);
        if (tmpValue != -1) {
            res += tmpValue;
        }

        tmpValue = MyHashMapGet(mp, pre_num);
        if (tmpValue == -1) {
            MyHashMapPut(mp, pre_num, 1);
        } else {
            MyHashMapPut(mp, pre_num, tmpValue + 1);
        }

    }
    return res;
}