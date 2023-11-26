class Solution {
public:
    
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) 
    {
        int n = nums.size();
        vector<int> tmp = nums;
        sort(tmp.begin(), tmp.end());
        unordered_map<int, int> par;
        unordered_map<int, queue<int>> group;
        vector<int> ans(n);
        
        for(int i = 0; i < n; i++)
        {
            if(i && tmp[i] - tmp[i-1] <= limit)
                par[tmp[i]] = par[tmp[i-1]];
            else 
                par[tmp[i]] = tmp[i];
            group[par[tmp[i]]].push(tmp[i]);
        }
        
        for(int i = 0; i < n; i++)
        {
            ans[i] = group[par[nums[i]]].front();
            group[par[nums[i]]].pop();
        }
        
        return ans;
    }
};
