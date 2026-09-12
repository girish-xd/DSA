class Solution {
    struct Interval {
        long long l, r, weight;
        int id;
    };

    struct Result {
        long long weight = -1;
        vector<int> indices;

        bool operator<(const Result& other) const {
            if (weight != other.weight) {
                return weight < other.weight;
            }
            return indices > other.indices;
        }
    };
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {(long long)intervals[i][0], 
                      (long long)intervals[i][1], 
                      (long long)intervals[i][2], 
                      i};
        }

    
        sort(arr.begin(), arr.end(), [](const Interval& a, const Interval& b) {
            if (a.r != b.r) return a.r < b.r;
            return a.l < b.l;
        });

        vector<vector<Result>> dp(5, vector<Result>(n + 1));

        for (int i = 0; i < n; ++i) {
            
            int low = 0, high = i - 1, p = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid].r < arr[i].l) {
                    p = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            for (int c = 1; c <= 4; ++c) {
                Result best = dp[c][i];
                if (c == 1) {
                    Result take;
                    take.weight = arr[i].weight;
                    take.indices = {arr[i].id};
                    if (best < take) best = take;
                } else if (p != -1 && dp[c - 1][p + 1].weight != -1) {
                    Result take;
                    take.weight = dp[c - 1][p + 1].weight + arr[i].weight;
                    take.indices = dp[c - 1][p + 1].indices;

                    auto it = lower_bound(take.indices.begin(), take.indices.end(), arr[i].id);
                    take.indices.insert(it, arr[i].id);

                    if (best < take) best = take;
                }

                dp[c][i + 1] = best;
            }
        }

        Result global_best;
        for (int c = 1; c <= 4; ++c) {
            if (global_best < dp[c][n]) {
                global_best = dp[c][n];
            }
        }

        return global_best.indices;
    
    }
};