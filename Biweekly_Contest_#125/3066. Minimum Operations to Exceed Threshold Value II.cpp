
// Time Complexity = O(n * logn)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    int minOperations(vector<int>& nums, int k) 
    {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for(ll x : nums)
            pq.push(x);
        int ans = 0;
        while(pq.size() >= 2 && pq.top() < k)
        {
            ll x = pq.top();
            pq.pop();
            ll y = pq.top();
            pq.pop();
            
            ans++;
            pq.push(2ll * min(x, y) + max(x, y));
        }
        
        return ans;
    }
};
