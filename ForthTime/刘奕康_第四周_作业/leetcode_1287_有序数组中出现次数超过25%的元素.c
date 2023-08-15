/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/element-appearing-more-than-25-in-sorted-array/
 *
 * 给你一个非递减的 有序 整数数组，已知这个数组中恰好有一个整数，它的出现次数超过数组元素总数的 25%。
 *
 * 请你找到并返回这个整数
 *
 * 示例
 * 输入：arr = [1,2,2,6,6,6,6,7,10]
 * 输出：6
 *
 * 提示：
 * 1 <= arr.length <= 10^4
 * 0 <= arr[i] <= 10^5
***/

int FindSpecialInteger(int* arr, int arrSize)
{
    int i = 0;
    while (i + arrSize/4 < arrSize && arr[i] != arr[i + arrSize/4]) {
        ++i;
    }

    return arr[i];
}