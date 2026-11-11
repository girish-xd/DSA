class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
       long long both = min(need1, need2);
        long long ans = both * min(1LL * costBoth, 1LL * cost1 + cost2);

        long long remaining1 = need1 - both;
        long long remaining2 = need2 - both;

        ans += remaining1 * min(1LL * cost1, 1LL * costBoth);
        ans += remaining2 * min(1LL * cost2, 1LL * costBoth);

        return ans; 
    }
};