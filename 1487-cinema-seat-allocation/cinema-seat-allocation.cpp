class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {

        // POTD - Solve again later by yourself.
        // Only seats 2-9 matter.
        // Represent reserved seats of each row using a bitmask.
        // Unreserved rows can always accommodate 2 groups.

        unordered_map<int, int> mp;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9) {
                mp[row] |= (1 << col);
            }
        }

        long long ans = 2LL * (n - mp.size());

        // Masks for:
        // 2,3,4,5
        int left = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);

        // 4,5,6,7
        int middle = (1 << 4) | (1 << 5) |
                     (1 << 6) | (1 << 7);

        // 6,7,8,9
        int right = (1 << 6) | (1 << 7) |
                    (1 << 8) | (1 << 9);

        for (auto &[row, mask] : mp) {
            bool canLeft = (mask & left) == 0;
            bool canMiddle = (mask & middle) == 0;
            bool canRight = (mask & right) == 0;

            if (canLeft && canRight) {
                ans += 2;
            } else if (canLeft || canMiddle || canRight) {
                ans += 1;
            }
        }

        return ans;
    }
};