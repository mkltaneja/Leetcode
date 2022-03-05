// DAY 1 (338. Counting Bits)=========================================================================================================================

// APPROACH 1 (Naive)
vector<int> countBits(int n) 
{
    vector<int> ans(n+1);
    for(int i = 0; i <= n; i++)
    {
        int x = i, cnt = 0;
        while(x)
        {
            x &= x-1;
            cnt++;
        }
        ans[i] = cnt;
    }
    return ans;
}

// APPROACH 2 (DP)

vector<int> countBits(int n) 
{
    vector<int> ans(n+1);
    for(int i = 1; i <= n; i++)
        ans[i] = ans[i & (i-1)] + 1;
    return ans;
}

// DAY 2 (392. Is Subsequence)=========================================================================================================================

bool isSubsequence(string s, string t) 
{
    int i = 0, j = 0, n = s.size(), m = t.size();
    while(i < n && j < m)
    {
        if(s[i] == t[j]) i++;
        j++;
    }
    return i == n;
}

// DAY 3 (413. Arithmetic Slices)=========================================================================================================================

int numberOfArithmeticSlices(vector<int>& nums) 
{
    int i = 2, j = 0, n = nums.size();
    int ans = 0;
    while(i < n)
    {
        if(2*nums[i-1] == nums[i-2] + nums[i]) 
            ans += i-j-1;
        else j = i-1;
        i++;
    }
    return ans;
}

// DAY 4 (799. Champagne Tower)=========================================================================================================================

double champagneTower(int poured, int query_row, int query_glass) 
{
    vector<double> glasses(1);
    glasses[0] = poured;

    for(int i = 0; i < query_row; i++)
    {
        vector<double> nglasses(i+2);
        for(int j = 0; j <= i; j++)
        {
            double x = (glasses[j] - 1) / 2.0;
            if(x <= 0) continue;
            nglasses[j] += x;
            nglasses[j+1] += x;
        }

        glasses = nglasses;
    }
    return min(1.0, glasses[query_glass]);
}
