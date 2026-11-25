class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
     int n = nums.size();
        if (n == 1) return 1;

        // 1. Build Suffix Array in O(N log N)
        vector<int> sa(n), rk(n), tmp(n);
        iota(sa.begin(), sa.end(), 0);
        for (int i = 0; i < n; ++i) rk[i] = nums[i];

        for (int k = 1; k < n; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rk[a] != rk[b]) return rk[a] < rk[b];
                int ra = (a + k < n) ? rk[a + k] : -1;
                int rb = (b + k < n) ? rk[b + k] : -1;
                return ra < rb;
            };
            sort(sa.begin(), sa.end(), cmp);

            tmp[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            }
            rk = tmp;
            if (rk[sa[n - 1]] == n - 1) break;
        }

        // 2. Build LCP Array in O(N) using Kasai's Algorithm
        // lcp[r] = LCP between sa[r - 1] and sa[r]
        vector<int> lcp(n, 0);
        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (rk[i] > 0) {
                int j = sa[rk[i] - 1];
                while (i + h < n && j + h < n && nums[i + h] == nums[j + h]) {
                    ++h;
                }
                lcp[rk[i]] = h;
                if (h > 0) --h;
            }
        }

        // 3. Find minimum unique prefix length across all suffixes
        int ans = n;
        for (int r = 0; r < n; ++r) {
            int left_lcp = (r > 0) ? lcp[r] : 0;
            int right_lcp = (r + 1 < n) ? lcp[r + 1] : 0;
            int min_len = max(left_lcp, right_lcp) + 1;

            // Ensure the subarray does not exceed array bounds
            if (sa[r] + min_len <= n) {
                ans = min(ans, min_len);
            }
        }

        return ans;   
    }
};