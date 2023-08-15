/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/count-negative-numbers-in-a-sorted-matrix/
 *
 * 给你一个 m * n 的矩阵 grid，矩阵中的元素无论是按行还是按列，都以非递增顺序排列。 请你统计并返回 grid 中 负数 的数目。
 *
 * 示例
 * 输入：grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
 * 输出：8
 * 解释：矩阵中共有 8 个负数。
 *
 * 输入：grid = [[3,2],[1,0]]
 * 输出：0
 *
 * 提示：
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 100
 * -100 <= grid[i][j] <= 100
***/

int countNegatives(int** grid, int gridSize, int* gridColSize){
    int rows = gridSize, cols = *gridColSize;
    int res = 0;
    int i = 0, j = cols - 1;

    //右上角到左下角
    for (i; i < rows; ++i) {
        while (j > -1 && grid[i][j] < 0) {
            --j;
        }
        //统计每一行负数的个数
        res += cols - 1 - j;
    }

    return res;
}