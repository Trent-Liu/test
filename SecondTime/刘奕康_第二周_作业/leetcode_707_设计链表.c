/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/design-linked-list/
 *
 * 你可以选择使用单链表或者双链表，设计并实现自己的链表。
 *
 * 单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针/引用。
 *
 * 如果是双向链表，则还需要属性 prev 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。
 *
 * 实现 MyLinkedList 类：
 *
 * MyLinkedList() 初始化 MyLinkedList 对象。
 * int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1 。
 * void addAtHead(int val) 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
 * void addAtTail(int val) 将一个值为 val 的节点追加到链表中作为链表的最后一个元素。
 * void addAtIndex(int index, int val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将 不会插入 到链表中。
 * void deleteAtIndex(int index) 如果下标有效，则删除链表中下标为 index 的节点。
 *
 * 示例
 * 输入
 * ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
 * [[], [1], [3], [1, 2], [1], [1], [1]]
 * 输出
 * [null, null, null, null, 2, null, 3]
 * 解释
 * MyLinkedList myLinkedList = new MyLinkedList();
 * myLinkedList.addAtHead(1);
 * myLinkedList.addAtTail(3);
 * myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
 * myLinkedList.get(1);              // 返回 2
 * myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
 * myLinkedList.get(1);              // 返回 3
 *
 * 提示：
 * 0 <= index, val <= 1000
 * 请不要使用内置的 LinkedList 库。
 * 调用 get、addAtHead、addAtTail、addAtIndex 和 deleteAtIndex 的次数不超过 2000 。
***/

#include<stdlib.h>

typedef struct DoubleListNode {
    int val;
    struct  DoubleListNode *prev, *next;
} DoubleListNode;

typedef struct {
    DoubleListNode *head, *tail;
    int size;
} MyLinkedList;

DoubleListNode* doubleListNodeCreate(int val)
{
    DoubleListNode * node = (DoubleListNode *)malloc(sizeof(struct DoubleListNode));
    if (node->next == NULL) {
        return NULL;
    }
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

MyLinkedList* MyLinkedListCreate()
{
    MyLinkedList *list = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = doubleListNodeCreate(-1);
    if (list->head == NULL) {
        return NULL;
    }
    list->tail = doubleListNodeCreate(-1);
    if (list->tail == NULL) {
        return NULL;
    }

    list->head->next = list->tail;
    list->tail->prev = list->head;

    list->size = 0;

    return list;
}

int MyLinkedListGet(MyLinkedList* obj, int index)
{
    if (index < 0 || index >= obj->size) {
        return -1;
    }

    DoubleListNode *cur = obj->head;
    for (int i = 0; i <= index; ++i) {
        cur = cur->next;
    }

    return cur->val;
}

void MyLinkedListAddAtIndex(MyLinkedList* obj, int index, int val)
{
    if (index > obj->size) {
        return;
    }
    if (index < 0) {
        index = 0;
    }

    DoubleListNode *pre = obj->head;
    for (int i = 0; i < index; ++i) {
        pre = pre->next;
    }
    DoubleListNode *next = pre->next;

    DoubleListNode *node = doubleListNodeCreate(val);
    if (node == NULL) {
        return;
    }
    node->prev = pre;
    node->next = next;
    pre->next = node;
    next->prev = node;

    ++obj->size;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val)
{
    MyLinkedListAddAtIndex(obj, 0, val);
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val)
{
    MyLinkedListAddAtIndex(obj, obj->size, val);
}

void MyLinkedListDeleteAtIndex(MyLinkedList* obj, int index)
{
    if (index < 0 || index >= obj->size) {
        return;
    }

    DoubleListNode *pre = obj->head;
    for (int i = 0; i < index; ++i) {
        pre = pre->next;
    }
    DoubleListNode *next = pre->next->next;

    DoubleListNode *tmp = pre->next;
    pre->next = next;
    next->prev = pre;
    free(tmp);

    --obj->size;

}

void MyLinkedListFree(MyLinkedList* obj)
{
    struct DoubleListNode *cur = obj->head;
    struct DoubleListNode *tmp = cur;

    while (cur) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(obj);
}