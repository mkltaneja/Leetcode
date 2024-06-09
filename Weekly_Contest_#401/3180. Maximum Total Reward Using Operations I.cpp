
// APPROACH 1 (Starting backwards, and finding next correct through upper_bound)

// Time Complexity = O(n*logn + n*mx*log(mx))
// Space Complexity = O(n*mx)

class Solution {
public:
    
    int dp[2002][5000];
//     int dfs(int i, int cnt, int n, vector<int> &arr)
//     {
//         if(i >= n)
//             return 0;
        
//         int j = upper_bound(arr.begin()+i, arr.end(), cnt) - arr.begin();
//         if(j == n)
//             return 0;
        
//         if(dp[i][cnt] != -1)
//             return dp[i][cnt];
        
//         int x = dfs(j+1, cnt + arr[j], n, arr) + arr[j];
//         int y = dfs(j+1, cnt, n, arr);
        
//         return dp[i][cnt] = max(x, y);
//     }
    
    int maxTotalReward(vector<int>& arr)
    {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int mx = arr[n-1];
        memset(dp, 0, n*mx);
        
        for (int i = n - 1; i >= 0; --i) 
        {
            for (int currSum = 0; currSum <= mx; ++currSum)
            {
                int j = upper_bound(arr.begin() + i, arr.end(), currSum) - arr.begin();
                if (j == n)
                    dp[i][currSum] = 0;
                else 
                {
                    int x = (j + 1 <= n ? dp[j + 1][currSum + arr[j]] + arr[j] : 0);
                    int y = (j + 1 <= n ? dp[j + 1][currSum] : 0);
                    dp[i][currSum] = max(x, y);
                }
            }
        }
        
        return dp[0][0];
        // return dfs(0, 0, n, arr);
    }
};



// APPROACH 2 (Starting backwards, and finding next correct through upper_bound)

// Time Complexity = O(n*logn + n*mx)
// Space Complexity = O(mx)

class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues)
    {
        int n = rewardValues.size();
        sort(rewardValues.begin(), rewardValues.end());
        int maxAns = 0;
        int mx = rewardValues[n-1];
        vector<bool> dp(mx+1, false);
        dp[0] = true;
        
        for(int reward : rewardValues)
        {
            for(int prevSum = 0; prevSum < reward; prevSum++)
            {
                if(!dp[prevSum]) continue;
                
                int currSum = prevSum + reward;
                if(currSum <= mx)
                    dp[currSum] = true;
                maxAns = max(maxAns, currSum);
            }
        }
        return maxAns;
    }
};
