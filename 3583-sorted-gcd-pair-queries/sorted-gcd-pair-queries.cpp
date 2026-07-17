class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {

        // POTD - Solve again later by yourself.
        // Idea:
        // 1. Count frequency of every number.
        // 2. For every gcd g, count how many numbers are divisible by g.
        // 3. Use inclusion-exclusion to find the number of pairs having gcd = g.
        // 4. Build prefix sums of pair counts.
        // 5. Binary search each query on the prefix sums to get the answer.

        int maxVal = *max_element(nums.begin(), nums.end());

        vector<long long> freq(maxVal + 1, 0);
        for (int x : nums) {
            freq[x]++;
        }

        // Count how many numbers are divisible by i.
        vector<long long> divisible(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++) {
            for (int j = i; j <= maxVal; j += i) {
                divisible[i] += freq[j];
            }
        }

        // exactPairs[g] = number of pairs whose gcd is exactly g.
        vector<long long> exactPairs(maxVal + 1, 0);

        for (int g = maxVal; g >= 1; g--) {
            long long cnt = divisible[g];
            long long totalPairs = cnt * (cnt - 1) / 2;

            for (int multiple = 2 * g; multiple <= maxVal; multiple += g) {
                totalPairs -= exactPairs[multiple];
            }

            exactPairs[g] = totalPairs;
        }

        // Prefix sums of pair counts.
        vector<long long> prefix(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++) {
            prefix[i] = prefix[i - 1] + exactPairs[i];
        }

        vector<int> ans;
        for (long long q : queries) {
            // Queries are 0-indexed, prefix counts are 1-indexed.
            int gcdValue = lower_bound(prefix.begin(), prefix.end(), q + 1) - prefix.begin();
            ans.push_back(gcdValue);
        }

        return ans;
    }
};