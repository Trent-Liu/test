/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/find-right-interval/
 *
 * 给你一个区间数组 intervals ，其中 intervals[i] = [starti, endi] ，且每个 starti 都 不同 。
 *
 * 区间 i 的 右侧区间 可以记作区间 j ，并满足 startj >= endi ，且 startj 最小化 。
 *
 * 返回一个由每个区间 i 的 右侧区间 在 intervals 中对应下标组成的数组。如果某个区间 i 不存在对应的 右侧区间 ，则下标 i 处的值设为 -1 。
 *
 * 示例
 * 输入：intervals = [[1,2]]
 * 输出：[-1]
 * 解释：集合中只有一个区间，所以输出-1。
 *
 * 输入：intervals = [[3,4],[2,3],[1,2]]
 * 输出：[-1,0,1]
 * 解释：对于 [3,4] ，没有满足条件的“右侧”区间。
 * 对于 [2,3] ，区间[3,4]具有最小的“右”起点;
 * 对于 [1,2] ，区间[2,3]具有最小的“右”起点。
 *
 * 输入：intervals = [[1,4],[2,3],[3,4]]
 * 输出：[-1,2,-1]
 * 解释：对于区间 [1,4] 和 [3,4] ，没有满足条件的“右侧”区间。
 * 对于 [2,3] ，区间 [3,4] 有最小的“右”起点。
 *
 * 提示：
 * 1 <= intervals.length <= 2 * 104
 * intervals[i].length == 2
 * -106 <= starti <= endi <= 106
 * 每个间隔的起点都 不相同
***/
#include<stdlib.h>

typedef struct {
    int start;
    int index;
} StartNode;

typedef struct {
    int end;
    int index;
} EndNode;

int CmpStart(const void *pa, const void *pb)
{
    return ((StartNode*)pa)->start - ((StartNode*)pb)->start;
}

int CmpEnd(const void *pa, const void *pb)
{
    return ((EndNode*)pa)->end - ((EndNode*)pb)->end;
}

int* FindRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize)
{
    *returnSize = intervalsSize;

    StartNode *startNodes = malloc(sizeof(StartNode) * intervalsSize);
    if (startNodes == NULL) {
        return NULL;
    }

    EndNode *endNodes = malloc(sizeof(EndNode) * intervalsSize);
    if (endNodes == NULL) {
        return NULL;
    }

    for (int i = 0; i < intervalsSize; ++i) {
        startNodes[i].start = intervals[i][0];
        startNodes[i].index = i;
        endNodes[i].end = intervals[i][1];
        endNodes[i].index = i;
    }

    qsort(startNodes, intervalsSize, sizeof(StartNode), CmpStart);
    qsort(endNodes, intervalsSize, sizeof(EndNode), CmpEnd);

    int *res = malloc(sizeof(int) * intervalsSize);

    for (int i = 0, j = 0; i < intervalsSize; ++i) {
        while (j < intervalsSize && endNodes[i].end > startNodes[j].start) {
            ++j;
        }
        if (j < intervalsSize) {
            res[endNodes[i].index] = startNodes[j].index;
        } else {
            res[endNodes[i].index] = -1;
        }
    }

    free(startNodes);
    free(endNodes);

    return res;
}