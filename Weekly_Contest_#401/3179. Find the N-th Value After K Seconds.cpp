
// Time Complexity = O(n*k)
// Space Complexity = O(n)

class Solution {
public:
    
    const int mod = 1e9 + 7;
    
    int valueAfterKSeconds(int n, int k) 
    {
        vector<int> arr(n, 1);
        for(int i = 1; i <= k; i++)
        {
            vector<int> prev = arr;
            for(int j = 1; j < n; j++)
                arr[j] = (arr[j] % mod + arr[j-1] % mod) % mod;
        }
        return arr[n-1];
    }
};
