class Solution {
public:
    
    #define ll long long
    #define f first
    #define s second
    
    long long getMaxFunctionValue(vector<int>& receiver, long long k) 
    {
        int dep = log2(k) + 1;
        int n = receiver.size();
        vector<vector<int>> nxt(dep, vector<int> (n, 0));
        vector<vector<ll>> sum(dep, vector<ll> (n, 0));
        for(int i = 0; i < n; i++)
        {
            nxt[0][i] = receiver[i];
            sum[0][i] = i + receiver[i];
        }
        
        for(int i = 1; i < dep; i++)
        {
            for(int j = 0; j < n; j++)
            {
                nxt[i][j] = nxt[i-1][nxt[i-1][j]];
                sum[i][j] = sum[i-1][j] + sum[i-1][nxt[i-1][j]] - nxt[i-1][j];
            }
        }
        
        ll maxSum = 0;
        for(int i = 0; i < n; i++)
        {
            ll currSum = i;
            int itr = i;
            for(int j = 0; j < dep; j++)
            {
                if((k >> j) & 1 ^ 1) continue;
                
                currSum = currSum + sum[j][itr] - itr;
                itr = nxt[j][itr];
            }
            maxSum = max(maxSum, currSum);
        }
        
        return maxSum;
    }
};
