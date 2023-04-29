class Solution {
public:
    int maximizeSum(vector<int>& nums, int k) 
    {
        priority_queue<int> pq;
        for(int x : nums)
            pq.push(x);
        int ans = 0;
        while(k--)
        {
            int x = pq.top();
            ans += x;
            pq.pop();
            pq.push(x+1);
        }
        return ans;
    }
};
