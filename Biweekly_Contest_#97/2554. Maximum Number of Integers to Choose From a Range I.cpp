class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) 
    {
        vector<bool> avail(n+1, true);
        for(int x : banned)
            if(x >= 1 && x <= n)
                avail[x] = false;

        int sum = 0, x = 1, cnt = 0;
        for(; x <= n && sum+x <= maxSum; x++)
            if(avail[x])
                sum += x, cnt++;
        return cnt;
    }
};
