
// Time Complexity = O(n * m * logn * logx)
// Space Complexity = O(n*m + n*logx)

class Solution {
public:
    
    const int TOTAL_BITS = 20;
    const int INF = 1e9;
    
    int findAnd(int l, int r, int n, vector<vector<int>> &prefZeros)
    {
        if(r == n)
            return INF;
        int andAns = 0;
        for(int bit = 0; bit < TOTAL_BITS; bit++)
        {
            int totalZeros = prefZeros[r][bit] - (l? prefZeros[l-1][bit] : 0);
            if(totalZeros == 0)
                andAns |= (1 << bit);
        }
        return andAns;
    }
    
    int findNextIdx(int i, int n, int andVal, vector<vector<int>> &prefZeros)
    {
        int lo = i, hi = n, andAns = INF;
        while(lo < hi)
        {
            int mid = (lo + hi) >> 1;
            andAns = findAnd(i, mid, n, prefZeros);
            if(andAns <= andVal)
                hi = mid;
            else lo = mid + 1;
        }
        andAns = findAnd(i, lo, n, prefZeros);
        return andAns == andVal? lo : -1;
    }
    
    int minimumValueSumDFS(int i, int j, int n, int m, vector<int> &nums, vector<int> &andValues, vector<vector<int>> &prefZeros, vector<vector<int>> &cache)
    {
        if(i == n) return j == m? 0 : INF;
        int &ans = cache[i][j];
        if(ans != INF)
            return ans;
        
        if(j && (andValues[j-1] & nums[i]) == andValues[j-1])
            ans = min(ans, minimumValueSumDFS(i+1, j, n, m, nums, andValues, prefZeros, cache) + nums[i] - nums[i-1]);
        
        int andIdx = j == m? -1 : findNextIdx(i, n, andValues[j], prefZeros);
        if(andIdx == -1)
            return ans;
        
        return ans = min(ans, minimumValueSumDFS(andIdx+1, j+1, n, m, nums, andValues, prefZeros, cache) + nums[andIdx]);
    }
    
    int minimumValueSum(vector<int>& nums, vector<int>& andValues)
    {
        int n = nums.size(), m = andValues.size();
        vector<vector<int>> cache(n, vector<int>(m+1, INF));
        vector<vector<int>> prefZeros(n, vector<int>(TOTAL_BITS, 0));
        for(int i = 0; i < n; i++)
            for(int bit = 0; bit < TOTAL_BITS; bit++)
                prefZeros[i][bit] = ((nums[i] & (1 << bit))? 0 : 1) + (i? prefZeros[i-1][bit] : 0);
        
        int ans = minimumValueSumDFS(0, 0, n, m, nums, andValues, prefZeros, cache);
        return ans >= INF? -1 : ans;
    }
};  
