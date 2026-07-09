class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                      vector<vector<int>>& queries) {
        // POTD - Solve again later by yourself.
        // Idea:
        // Since nums is sorted, if nums[i] and nums[i-1] differ by more than
        // maxDiff, then no path can cross this gap. So we assign the same
        // component to consecutive indices while adjacent difference <=
        // maxDiff. Two nodes have a path iff they belong to the same component.

        vector<int> comp(n, 0);

        int id = 0;
        comp[0] = id;

        for (int i = 1; i < n; i++) {
            if (nums[i] - nums[i - 1] > maxDiff)
                id++;
            comp[i] = id;
        }

        vector<bool> ans;
        for (auto& q : queries) {
            ans.push_back(comp[q[0]] == comp[q[1]]);
        }

        return ans;
    }
};