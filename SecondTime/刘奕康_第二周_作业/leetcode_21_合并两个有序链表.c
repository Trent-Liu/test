/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/merge-two-sorted-lists/
 *
 * 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 *
 * 示例
 * 输入：l1 = [1,2,4], l2 = [1,3,4]
 * 输出：[1,1,2,3,4,4]
 *
 * 输入：l1 = [], l2 = []
 * 输出：[]
 *
 * 输入：l1 = [], l2 = [0]
 * 输出：[0]
 *
 * 提示：
 * 两个链表的节点数目范围是 [0, 50]
 * -100 <= Node.val <= 100
 * l1 和 l2 均按 非递减顺序 排列
***/
#include<stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* MergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode dummy;
    struct ListNode* dummyNode = &dummy;
    dummyNode->next = NULL;

    while (list1 && list2) {
        if (list1->val > list2->val) {
            dummyNode->next = list2;
            list2 = list2->next;
            dummyNode = dummyNode->next;
        } else {
            dummyNode->next = list1;
            list1 = list1->next;
            dummyNode = dummyNode->next;
        }
    }

    if (list1) {
        dummyNode->next = list1;
    }
    if (list2) {
        dummyNode->next = list2;
    }

    return dummy.next;
}