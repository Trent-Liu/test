/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/subarray-sums-divisible-by-k/description/
 *
 * 给定一个整数数组 nums 和一个整数 k ，返回其中元素之和可被 k 整除的（连续、非空） 子数组 的数目。
 *
 *子数组 是数组的 连续 部分。
 *
 * 示例
 * 输入：nums = [4,5,0,-2,-3,1], k = 5
 * 输出：7
 * 解释：
 * 有 7 个子数组满足其元素之和可被 k = 5 整除：
 * [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 *
 * 输入: nums = [5], k = 9
 * 输出: 0
 *
 * 提示：
 * 1 <= nums.length <= 3 * 104
 * -104 <= nums[i] <= 104
 * 2 <= k <= 104
 *
***/

#include<stdlib.h>

typedef struct {
    int key;
    int count;
    UT_hash_handle hh;
} HashNode, *HashTable;

int SubarraysDivByK(int* nums, int numsSize, int k){
    HashTable hl = (HashTable)malloc(sizeof(HashNode));
    hl = NULL;
    HashNode *temp;

    int presum = 0;
    int result = 0;

    for (int i = 0; i < numsSize; i++) {
        presum += nums[i];
        int modules = (presum % k + k) % k;

        if (modules == 0) {
            result += 1;
        }

        HASH_FIND_INT(hl, &(modules), temp);
        if (temp != NULL) {
            result += temp->count;
            temp->count += 1;
        } else {
            temp = malloc(sizeof(HashNode));
            temp->key = modules;
            temp->count = 1;
            HASH_ADD_INT(hl, key, temp);
        }
    }
    return result;
}
