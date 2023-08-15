/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/trapping-rain-water/submissions/
 *
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 *
 * 示例
 * 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * 输出：6
 * 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
 *
 * 输入：height = [4,2,0,3,2,5]
 * 输出：9
 *
 * 提示：
 * n == height.length
 * 1 <= n <= 2 * 104
 * 0 <= height[i] <= 105
***/

int Min(int a,int b)
{
    return a <= b ? a : b;

}

int Trap(int* height, int heightSize)
{
    if (heightSize == 0) {
        return 0;
    }
    int res = 0;
    int st[heightSize];
    int top = 0;

    for (int i = 0; i < heightSize; ++i) {
        while (top != 0 && height[i] > height[st[top-1]]) {
            int topIndex = st[top-1];
            --top;

            if (top == 0) {
                break;
            }

            int left = st[top-1];
            int width = i - left - 1;
            int high = Min(height[left], height[i]) - height[topIndex];
            res += width * high;
        }
        st[top] = i;
        ++top;
    }
    return res;
}