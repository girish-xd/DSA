class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {

        // POTD - Solve again later by yourself.

        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n, INF);

        int left = 0;
        long long sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target) {
                sum -= arr[left++];
            }

            if (sum == target) {
                int len = right - left + 1;

                // A previous subarray must end before 'left'.
                if (left > 0 && best[left - 1] != INF)
                    ans = min(ans, len + best[left - 1]);

                best[right] = len;
            }

            // Carry forward the shortest subarray seen so far.
            if (right > 0)
                best[right] = min(best[right], best[right - 1]);
        }

        return ans == INF ? -1 : ans;
    }
};