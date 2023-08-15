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