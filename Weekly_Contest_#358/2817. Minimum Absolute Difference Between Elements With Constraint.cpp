class Solution {
public:
    
    #define f first
    #define s second
    int minAbsoluteDifference(vector<int>& nums, int x) 
    {
        if(x == 0) return 0;
        int n = nums.size();
        vector<vector<int>> numsi(n, vector<int>(2));
        for(int i = 0; i < n; i++)
            numsi[i] = {nums[i], i};
        sort(numsi.begin(), numsi.end());
        
        priority_queue<pair<int,int>> pq1;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq2;
                
        int ans = INT_MAX;
        for(int i = 0; i < n; i++)
        {
            int ele = numsi[i][0];
            int j = numsi[i][1];
            
            while(!pq1.empty() && abs(pq1.top().f - j) >= x)
            {
                ans = min(ans, abs(pq1.top().s - ele));
                pq1.pop();
            }
            while(!pq2.empty() && abs(pq2.top().f - j) >= x)
            {
                ans = min(ans, abs(pq2.top().s - ele));
                pq2.pop();
            }
            pq1.push({j, ele});
            pq2.push({j, ele});
        }
        
        return ans;
    }
};
