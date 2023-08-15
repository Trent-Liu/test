/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/add-two-numbers/description/
 *
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 *
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 *
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * 示例
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 *
 * 输入：l1 = [0], l2 = [0]
 * 输出：[0]
 *
 * 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * 输出：[8,9,9,9,0,0,0,1]
 *
 * 提示：
 * 每个链表中的节点数在范围 [1, 100] 内
 * 0 <= Node.val <= 9
 * 题目数据保证列表表示的数字不含前导零
***/
#include<stdio.h>
#include<stdlib.h>

struct ListNode {
     int val;
     struct ListNode *next;
 };

struct ListNode* AddTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode* cur1 = l1;
    struct ListNode* cur2 = l2;

    struct ListNode dummy;
    struct ListNode *dummyNode = &dummy;
    dummyNode->next = NULL;

    int carry = 0;

    while (cur1 != NULL || cur2 != NULL) {
        int add1 = 0, add2 = 0;
        if (cur1) {
            add1 = cur1->val;
            cur1 = cur1->next;
        }
        if (cur2) {
            add2 = cur2->val;
            cur2 = cur2->next;
        }

        int res = add1 + add2 + carry;

        struct ListNode *tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (tmp == NULL) {
            return NULL;
        }
        tmp->val = res%10;
        dummyNode->next = tmp;
        dummyNode = dummyNode->next;
        dummyNode->next = NULL;

        carry = res/10;
    }

    if (carry != 0) {
        struct ListNode *tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (tmp == NULL) {
            return NULL;
        }
        tmp->val = carry;
        dummyNode->next = tmp;
        dummyNode = dummyNode->next;
        dummyNode->next = NULL;
    }

    return dummy.next;
}