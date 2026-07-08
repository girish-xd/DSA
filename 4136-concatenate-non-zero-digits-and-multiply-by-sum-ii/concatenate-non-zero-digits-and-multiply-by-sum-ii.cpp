class Solution {
public:
    static const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {

        // TODO: Daily Challenge (solution taken for streak).
        // Revisit and solve from scratch later.
        // Concepts: Binary Search + Prefix Sum + Prefix Concatenation.

        vector<int> pos, digit;

        // Store positions and values of all non-zero digits
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digit.push_back(s[i] - '0');
            }
        }

        int n = digit.size();

        // pow10[i] = 10^i % MOD
        vector<long long> pow10(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        // prefVal[i] = concatenated number of first i non-zero digits
        vector<long long> prefVal(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefVal[i + 1] = (prefVal[i] * 10 + digit[i]) % MOD;

        // prefSum[i] = sum of first i non-zero digits
        vector<long long> prefSum(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefSum[i + 1] = prefSum[i] + digit[i];

        vector<int> ans;

        for (auto &q : queries) {

            int L = q[0], R = q[1];

            // First non-zero digit inside [L, R]
            auto it1 = lower_bound(pos.begin(), pos.end(), L);

            // First non-zero digit after R
            auto it2 = upper_bound(pos.begin(), pos.end(), R);

            // No non-zero digit exists
            if (it1 == it2) {
                ans.push_back(0);
                continue;
            }

            int left = it1 - pos.begin();
            int right = (it2 - pos.begin()) - 1;

            int len = right - left + 1;

            // Extract concatenated value of digits[left...right]
            long long x = (prefVal[right + 1]
                         - (prefVal[left] * pow10[len]) % MOD
                         + MOD) % MOD;

            // Sum of digits in the range
            long long sum = prefSum[right + 1] - prefSum[left];

            ans.push_back((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
};
// TODO: Daily Challenge (Didn't solve myself).
// Revisit and solve from scratch later.
// Key concepts: Binary Search + Prefix Sum + Prefix Number (Rolling Hash idea).