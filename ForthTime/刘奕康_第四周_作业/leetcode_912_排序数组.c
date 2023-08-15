/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/sort-an-array/
 *
 * 给你一个整数数组 nums，请你将该数组升序排列。
 *
 * 示例
 * 输入：nums = [5,2,3,1]
 * 输出：[1,2,3,5]
 *
 * 输入：nums = [5,1,1,2,0,0]
 * 输出：[0,0,1,1,2,5]
 *
 * 提示：
 * 1 <= nums.length <= 5 * 104
 * -5 * 104 <= nums[i] <= 5 * 104
***/

#include <stdlib.h>

void MergeSort(int* nums, int left, int right, int *tmp)
{
    if (left >= right) {
        return;
    }
    int mid = left - (left - right) / 2;

    MergeSort(nums, left, mid, tmp);
    MergeSort(nums, mid + 1, right, tmp);

    for (int i = left; i <= right; ++i) {
        tmp[i] = nums[i];
    }

    int i = left, j = mid + 1;
    for (int k = left; k <= right; ++k) {
        if (j == right + 1 || (i <= mid && tmp[i] < tmp[j])) {
            nums[k] = tmp[i++];
        } else if (i == mid + 1 || (j <= right) && tmp[i] >= tmp[j]) {
            nums[k] = tmp[j++];
        }
    }
}

//使用堆排，快排题目1464已经实现。
int* SortArray(int* nums, int numsSize, int* returnSize){
    *returnSize = numsSize;

    int *tmp = malloc(sizeof(int) * numsSize);
    if (tmp == NULL) {
        return NULL;
    }

    MergeSort(nums, 0, numsSize - 1, tmp);

    free(tmp);

    return nums;
}