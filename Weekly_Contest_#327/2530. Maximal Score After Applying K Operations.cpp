class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) 
    {
        priority_queue<int> pq;
        for(int x : nums)
            pq.push(x);
        
        long long ans = 0;
        while(k--)
        {
            long long tp = pq.top();
            pq.pop();
            pq.push((tp + 2) / 3);
            ans += tp;
        }
        
        return ans;
    }
};
