
// Contest Submission

class Solution {
public:
    
    int MOD = 1e9 + 7;
    
    static bool comp(vector<int> &a, vector<int> &b)
    {
        return a[0] == b[0]? a[1] > b[1] : a[0] < b[0];
    }
    
    int numberOfGoodPartitions(vector<int>& nums) 
    {
        unordered_map<int,pair<int,int>> mp;
        vector<vector<int>> grps;
        for(int i = 0; i < nums.size(); i++)
        {
            if(mp.count(nums[i]))
                mp[nums[i]].second = i;
            else
            {
                mp[nums[i]].first = i;
                mp[nums[i]].second = i;
            }
        }
        for(auto p : mp)
            grps.push_back({p.second.first, p.second.second});
        
        sort(grps.begin(), grps.end(), comp);
        int last = -1, parts = 0;
        
        for(vector<int> &g : grps)
        {
            if(g[0] <= last) last = max(last, g[1]);
            else 
            {
                last = g[1];
                parts++;
            }
        }
        
        int ans = 1;
        while(--parts)
        {
            ans = (ans % MOD * 2 % MOD) % MOD;
        }
        
        return ans;
    }
};
