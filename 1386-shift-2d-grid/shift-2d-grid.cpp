class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        
        // POTD - Solve again later by yourself.
        // Idea:
        // Treat the grid as a 1D circular array.
        // New position of an element = (old_position + k) % (m * n).

        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        k %= total;

        vector<vector<int>> ans(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                int oldPos = i * n + j;
                int newPos = (oldPos + k) % total;

                int newRow = newPos / n;
                int newCol = newPos % n;

                ans[newRow][newCol] = grid[i][j];
            }
        }

        return ans;
    }
};