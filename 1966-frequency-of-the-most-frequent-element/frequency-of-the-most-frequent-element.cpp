class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
         // TODO: Revisit after learning Sliding Window (Variable Size Window).
        // Optimal approach:
        // Sorting + Sliding Window + Running Sum

        sort(nums.begin(), nums.end());

        long long sum = 0;
        int left = 0;
        int ans = 1;

        for (int right = 0; right < nums.size(); right++) {

            sum += nums[right];

            while ((long long)nums[right] * (right - left + 1) - sum > k) {
                sum -= nums[left];
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};