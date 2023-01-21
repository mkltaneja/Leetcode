class Solution {
public:
    
    #define ll long long
    #define f first
    #define s second
    
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        int n = nums1.size();
        vector<pair<ll,ll>> nums(n);
        for(int i = 0; i < n; i++)
            nums[i] = {nums2[i], nums1[i]};
        sort(nums.begin(), nums.end());
        
        priority_queue<ll,vector<ll>, greater<ll>> pq;
        ll sum = 0;
        ll ans = INT_MIN;
        for(int i = n-1; i >= 0; i--)
        {
            sum += nums[i].s;
            pq.push(nums[i].s);
            if(pq.size() > k)
            {
                sum -= pq.top();
                pq.pop();
            }
            if(pq.size() < k) continue;
            
            ans = max(ans, sum*nums[i].f);
        }
        
        return ans;
    }
};
