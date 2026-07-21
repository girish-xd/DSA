class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        int active = 0;
        for (char c : s) {
            if (c == '1') active++;
        }

        // POTD - Solve again later by yourself.
        // Idea:
        // Augment the string with '1' at both ends.
        // For every block of 1's that is surrounded by 0's,
        // removing it merges the adjacent zero blocks along with
        // this 1-block into one large zero block.
        // If that zero block is surrounded by 1's, we can turn it
        // entirely into 1's.
        //
        // Net gain = length(left zero block) + length(one block)
        //            + length(right zero block) - length(one block)
        //          = length(left zero block) + length(right zero block)
        //            if you think in gains over active count,
        // but it's easiest to compute directly as:
        // active - oneLen + (leftZero + oneLen + rightZero).

        string t = "1" + s + "1";
        int m = t.size();

        vector<pair<char, int>> groups;
        for (int i = 0; i < m;) {
            int j = i;
            while (j < m && t[j] == t[i]) {
                j++;
            }
            groups.push_back({t[i], j - i});
            i = j;
        }

        int ans = active;

        // Pattern needed: 0-block, 1-block, 0-block.
        for (int i = 1; i + 1 < (int)groups.size(); i++) {
            if (groups[i].first == '1' &&
                groups[i - 1].first == '0' &&
                groups[i + 1].first == '0') {

                int oneLen = groups[i].second;
                int leftZero = groups[i - 1].second;
                int rightZero = groups[i + 1].second;

                int cur = active - oneLen + (leftZero + oneLen + rightZero);
                ans = max(ans, cur);
            }
        }

        return ans;
    }
};