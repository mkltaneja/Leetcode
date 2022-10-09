class Solution {
public:
    vector<int> findArray(vector<int>& pref) 
    {
        int n = pref.size();
        vector<int> ans(n);
        for(int i = 0; i < n; i++)
            ans[i] = pref[i] ^ (i? pref[i-1] : 0);
        return ans;
    }
};
