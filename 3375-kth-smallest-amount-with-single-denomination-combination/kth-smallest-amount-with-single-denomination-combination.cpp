class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // Step 1: Remove redundant denominations (multiples of smaller coins)
        std::sort(coins.begin(), coins.end());
        std::vector<int> filtered_coins;
        for (int coin : coins) {
            bool is_multiple = false;
            for (int base : filtered_coins) {
                if (coin % base == 0) {
                    is_multiple = true;
                    break;
                }
            }
            if (!is_multiple) {
                filtered_coins.push_back(coin);
            }
        }

        int n = filtered_coins.size();

        // Helper lambda for LCM using std::gcd (C++17)
        auto lcm = [](long long a, long long b) -> long long {
            return (a / std::gcd(a, b)) * b;
        };

        // Step 2: Precompute (LCM, sign) for all non-empty subsets
        struct Subset {
            long long lcm_val;
            int sign; // +1 for odd subset sizes, -1 for even
        };
        std::vector<Subset> subsets;
        subsets.reserve((1 << n) - 1);

        for (int mask = 1; mask < (1 << n); ++mask) {
            long long current_lcm = 1;
            int size = 0;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    current_lcm = lcm(current_lcm, filtered_coins[i]);
                    ++size;
                }
            }
            int sign = (size % 2 == 1) ? 1 : -1;
            subsets.push_back({current_lcm, sign});
        }

        // Step 3: Function to count valid amounts <= x using PIE
        auto count_multiples = [&](long long x) -> long long {
            long long total = 0;
            for (const auto& [lcm_val, sign] : subsets) {
                total += sign * (x / lcm_val);
            }
            return total;
        };

        // Step 4: Binary search on the answer
        long long low = 1;
        long long high = 1LL * filtered_coins[0] * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (count_multiples(mid) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller valid amount
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};