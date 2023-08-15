/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/sort-array-by-increasing-frequency/
 *
 * 给你一个整数数组 nums ，请你将数组按照每个值的频率 升序 排序。如果有多个值的频率相同，请你按照数值本身将它们 降序 排序。
 *
 * 请你返回排序后的数组。
 *
 * 示例
 * 输入：nums = [1,1,2,2,2,3]
 * 输出：[3,1,1,2,2,2]
 * 解释：'3' 频率为 1，'1' 频率为 2，'2' 频率为 3 。
 *
 * 输入：nums = [2,3,1,3,2]
 * 输出：[1,3,3,2,2]
 * 解释：'2' 和 '3' 频率都为 2 ，所以它们之间按照数值本身降序排序。
 *
 * 输入：nums = [-1,1,-6,4,5,-6,1,4,1]
 * 输出：[5,-1,4,4,-6,-6,1,1,1]
 *
 * 提示：
 * 1 <= nums.length <= 100
 * -100 <= nums[i] <= 100
***/

struct HashNode {
    int val;
    int count;
    UT_hash_handle hh;
};

int CmpCount(const struct HashNode *a, const struct HashNode *b)
{
    if (a->count == b->count) {
        return b->val = a->val;
    } else {
        return a->count - b->count;
    }
}

int* FrequencySort(int* nums, int numsSize, int* returnSize)
{
    struct HashNode *mp = NULL;
    struct HashNode *hashTmp = NULL;

    *returnSize = numsSize;

    for(int i = 0; i < numsSize; i++) {
        HASH_FIND_INT(mp, &nums[i], hashTmp);
        if(hashTmp == NULL) {
            hashTmp = (struct HashNode*)malloc(sizeof *hashTmp);
            hashTmp->val = nums[i];
            hashTmp->count = 1;
            HASH_ADD_INT(mp, val, hashTmp);
        } else {
            hashTmp->count++;
        }
    }

    HASH_SORT(mp, CmpCount);

    int i = 0;
    for (hashTmp = mp; hashTmp != NULL; hashTmp = hashTmp->hh.next) {
        while(hashTmp->count--) {
            nums[i++] = hashTmp->val;
        }
    }

    struct HashNode *cur, *tmp;
    HASH_ITER(hh, mp, cur, tmp) {
        HASH_DEL(mp, cur);
        free(cur);
    }

    return nums;
}