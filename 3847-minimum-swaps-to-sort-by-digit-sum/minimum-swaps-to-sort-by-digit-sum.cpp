class Solution {
public:
   int digitSum(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        // POTD - Solve again later by yourself.
        int n = nums.size();
        vector<pair<int, int>> sorted;

        for (int i = 0; i < n; i++) {
            sorted.push_back({digitSum(nums[i]), nums[i]});
        }

        sort(sorted.begin(), sorted.end());

        unordered_map<int, int> targetIndex;
        for (int i = 0; i < n; i++) {
            targetIndex[sorted[i].second] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || targetIndex[nums[i]] == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = targetIndex[nums[j]];
                cycleSize++;
            }

            swaps += cycleSize - 1;
        }

        return swaps;   
    }
};