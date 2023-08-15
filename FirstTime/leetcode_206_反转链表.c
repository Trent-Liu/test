/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/reverse-linked-list/description/
 *
 * 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 *
 * 示例
 * 输入：head = [1,2,3,4,5]
 * 输出：[5,4,3,2,1]
 *
 * 输入：head = [1,2]
 * 输出：[2,1]
 *
 * 输入：head = []
 * 输出：[]
 *
 * 提示：
 * 链表中节点的数目范围是 [0, 5000]
 * -5000 <= Node.val <= 5000
***/

#include <stdio.h>

//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

//递归写法
struct ListNode* reverseList(struct ListNode* head){
    //判断出新的链表头，即递归终止条件
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* newHead = reverseList(head->next);
    //后链前
    head->next->next = head;
    //前变尾
    head->next = NULL;

    return newHead;
}