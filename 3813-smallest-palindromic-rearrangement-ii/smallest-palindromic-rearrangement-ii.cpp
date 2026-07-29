#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    static const int INF = 1000007; // Cap values above k (since max k = 10^6)

    // Computes nCr capped at INF without overflow
    int nCk(int n, int k) {
        if (k < 0 || k > n) return 0;
        if (k == 0 || k == n) return 1;
        k = min(k, n - k);
        long long res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * (n - i + 1) / i;
            if (res >= INF) return INF;
        }
        return (int)res;
    }

    // Computes the multinomial coefficient for character frequencies
    int countArrangements(const vector<int>& count) {
        int total = 0;
        for (int c : count) total += c;

        long long res = 1;
        for (int freq : count) {
            if (freq == 0) continue;
            res *= nCk(total, freq);
            if (res >= INF) return INF;
            total -= freq;
        }
        return (int)res;
    }

public:
    string smallestPalindrome(string s, int k) {
        int n = s.length();
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        vector<int> halfFreq(26, 0);
        char midChar = 0;
        for (int c = 0; c < 26; ++c) {
            halfFreq[c] = freq[c] / 2;
            if (freq[c] % 2 != 0) {
                midChar = 'a' + c;
            }
        }

        // Check if total distinct palindromic permutations are fewer than k
        if (countArrangements(halfFreq) < k) {
            return "";
        }

        int m = n / 2;
        string firstHalf = "";
        firstHalf.reserve(m);

        // Build the left half character by character
        for (int i = 0; i < m; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (halfFreq[c] == 0) continue;

                halfFreq[c]--; // Tentative placement
                int ways = countArrangements(halfFreq);

                if (ways >= k) {
                    firstHalf.push_back('a' + c);
                    break; // Keep character c at position i
                } else {
                    k -= ways;
                    halfFreq[c]++; // Undo tentative placement
                }
            }
        }

        // Reconstruct full palindrome
        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        if (n % 2 != 0) {
            return firstHalf + midChar + secondHalf;
        } else {
            return firstHalf + secondHalf;
        }
    }
};