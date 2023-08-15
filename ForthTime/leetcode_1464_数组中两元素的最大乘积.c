/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/maximum-product-of-two-elements-in-an-array/
 *
 * 给你一个整数数组 nums，请你选择数组的两个不同下标 i 和 j，使 (nums[i]-1)*(nums[j]-1) 取得最大值。
 *
 * 请你计算并返回该式的最大值。
 *
 * 示例
 * 输入：nums = [3,4,5,2]
 * 输出：12
 * 解释：如果选择下标 i=1 和 j=2（下标从 0 开始），则可以获得最大值，(nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12 。
 *
 * 输入：nums = [1,5,4,5]
 * 输出：16
 * 解释：选择下标 i=1 和 j=3（下标从 0 开始），则可以获得最大值 (5-1)*(5-1) = 16 。
 *
 * 输入：nums = [3,7]
 * 输出：12
 *
 * 提示：
 * 2 <= nums.length <= 500
 * 1 <= nums[i] <= 10^3
***/

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
