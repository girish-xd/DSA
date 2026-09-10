class Solution {
public:
    int ans = 0;

    pair<int,int> dfs(TreeNode* root) {
        if (!root) return {0, 0};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        int sum = root->val + left.first + right.first;
        int cnt = 1 + left.second + right.second;

        if (root->val == sum / cnt)
            ans++;

        return {sum, cnt};
    }

    int averageOfSubtree(TreeNode* root) {

        // POTD - Solve again later by yourself.

        dfs(root);
        return ans;
    }
};