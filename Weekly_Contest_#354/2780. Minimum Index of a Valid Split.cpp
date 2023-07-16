class Solution {
public:
    int minimumIndex(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> dom1(n), dom2(n);
        priority_queue<pair<int,int>> pq;
        unordered_map<int,int> mp;
        priority_queue<pair<int,int>> pq1;
        unordered_map<int,int> mp1;
        
        for(int i = 0; i < n; i++)
        {
            mp[nums[i]]++;
            pq.push({mp[nums[i]], nums[i]});
            if(pq.top().first * 2 > (i+1))
                dom1[i] = pq.top().second;
        }
        
        int ans = -1;
        for(int i = n-1; i >= 0; i--)
        {
            mp1[nums[i]]++;
            pq1.push({mp1[nums[i]], nums[i]});
            if(pq1.top().first * 2 > (n-i))
                dom2[i] = pq1.top().second;
            
            if(i == 0 || dom1[i-1] == 0 || dom2[i] == 0) continue;
            ans = dom1[i-1] == dom2[i]? i - 1 : ans;
        }
        
        return ans;
    }
};
