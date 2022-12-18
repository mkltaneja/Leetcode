class Solution {
public:
    int similarPairs(vector<string>& words) 
    {
        unordered_map<int,int> mp;
        int ans = 0;
        for(string &word : words)
        {
            int x = 0;
            for(char &c : word)
                x |= (1 << (c-'a'));
            ans += mp[x]++;
        }
        
        return ans;
    }
};
