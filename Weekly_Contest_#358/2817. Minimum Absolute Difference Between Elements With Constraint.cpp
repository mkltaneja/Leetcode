
// APPROACH 1 (Using priority Queue and Next Greater Element type approach) --> time = O(n + 3*n*logn)

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

// APPROACH 2 (Sliding window -> considering elements outside x-sized window using set) --> time = O((n-x)*log(n-x)) --> [OPTIMIZED]

class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) 
    {
        int n = nums.size();
        set<int> st;
        int ans = INT_MAX;
        for(int i = x; i < n; i++)
        {
            st.insert(nums[i-x]);
            auto itr = st.lower_bound(nums[i]);
            if(itr != st.end())
                ans = min(ans, *itr - nums[i]);
            if(itr != st.begin())
                ans = min(ans, nums[i] - *(--itr));
        }
        
        return ans;
    }
};
