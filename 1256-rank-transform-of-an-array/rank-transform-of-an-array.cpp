class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> temp = arr;
        vector<int> ans;
        sort(temp.begin(), temp.end());
        unordered_map<int, int> mp;
        int rank = 1;
        for (int i = 0; i < temp.size(); i++) {
            if (i == 0 || temp[i] != temp[i - 1]) {
                mp[temp[i]] = rank;
                rank++;
            }
        }
        for (int i = 0; i < arr.size(); i++) {
            ans.push_back(mp[arr[i]]);
        }
        return ans;
    }
};