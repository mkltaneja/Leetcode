class Solution {
public:
    int maxSum(vector<int>& nums) 
    {
        unordered_map<int,vector<int>> mp;
        for(int x : nums)
        {
            int tmp = x;
            int y = 0;
            while(x)
            {
                y = max(y, x%10);
                x /= 10;
            }
            mp[y].push_back(tmp);
        }
        
        int ans = -1;
        for(auto p : mp)
        {
            if(p.second.size() < 2) continue;
            sort(p.second.begin(), p.second.end());
            ans = max(ans, p.second.back() + p.second[p.second.size()-2]);
        }
        
        return ans;
    }
};
