class Solution {
public:
    int destroyTargets(vector<int>& nums, int space) 
    {
        unordered_map<int,int> cnt;
        unordered_map<int,int> mp;
        for(int x : nums)
        {
            if(!mp.count(x % space))
                mp[x % space] = x;
            else mp[x % space] = min(mp[x % space], x);
            cnt[x % space]++;
        }
        
        int mx = -1, ans = INT_MAX;
        for(auto p : cnt)
        {
            if(p.second > mx) 
            {
                mx = p.second;
                ans = mp[p.first];
            }
            else if(p.second == mx) ans = min(ans, mp[p.first]);
        }
        
        return ans;
    }
};
