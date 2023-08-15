/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/longest-univalue-path/
 *
 * 给定一个二叉树的 root ，返回 最长的路径的长度 ，这个路径中的 每个节点具有相同值 。 这条路径可以经过也可以不经过根节点。
 *
 * 两个节点之间的路径长度 由它们之间的边数表示。
 *
 * 示例
 * 输入：root = [5,4,5,1,1,5]
 * 输出：2
 *
 * 输入：root = [1,4,5,4,4,5]
 * 输出：2
 *
 * 提示：
 * 树的节点数的范围是 [0, 104]
 * -1000 <= Node.val <= 1000
 * 树的深度将不超过 1000
 *
***/
#include <stdio.h>

int Max(int a, int b)
{
    return a > b ? a : b;
}

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int Dfs(struct TreeNode *root, int *res)
{
    if (root == NULL) {
        return 0;
    }

    int leftLength = Dfs(root->left, res);
    int rightLength = Dfs(root->right, res);

    int left = 0;
    int right = 0;

    if (root->left && root->left->val == root->val) {
        left = leftLength + 1;
    }

    if (root->right && root->right->val == root->val) {
        right = rightLength + 1;
    }

    *res = Max(*res, left + right);
    return Max(left, right);
}

int LongestUnivaluePath(struct TreeNode* root)
{
    int res = 0;
    Dfs(root, &res);

    return res;
}

