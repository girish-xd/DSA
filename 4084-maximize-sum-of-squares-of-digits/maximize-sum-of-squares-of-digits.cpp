class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
       if (sum > 9LL * num) {
            return "";
        }
        
        int nines = sum / 9;
        int rem = sum % 9;
        
        string ans = "";
        ans.reserve(num);
        
        // Place as many 9s as possible
        ans.append(nines, '9');
        
        // Place the remainder digit if it exists
        if (rem > 0) {
            ans.push_back('0' + rem);
        }
        
        // Fill the rest of the positions with '0's
        if (ans.length() < num) {
            ans.append(num - ans.length(), '0');
        }
        
        return ans; 
    }
};