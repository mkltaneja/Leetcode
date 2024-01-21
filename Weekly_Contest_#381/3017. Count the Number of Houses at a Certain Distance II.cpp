// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    
    void updateCount(int left, int right, int count, vector<ll> &ans)
    {
        if(left > right) return;
        ans[left] += count;
        ans[right+1] -= count;
    }
    
    vector<long long> countOfPairs(int n, int x, int y) 
    {
        x--, y--;
        if(x > y) swap(x, y);
        
        vector<ll> ans(n+2);
        for(int i = 0; i < n; i++)
        {
            updateCount(1, i, 1, ans);
            updateCount(1, n-(i+1), 1, ans);
            if(y - x <= 1) continue;
            
            if(i <= x)
            {
                int p = ((x + y) / 2) + 1;
                int dist = x-i + 1;
                updateCount(p-i, n-i-1, -1, ans);
                updateCount(dist, dist + (y-p), 1, ans);
                updateCount(dist + 1, dist + (n-y-1), 1, ans);
            }
            else if(i >= y)
            {
                int p = ((x + y - 1) / 2);
                int dist = i-y + 1;
                updateCount(i-p, i, -1, ans);
                updateCount(dist, dist + (p-x), 1, ans);
                updateCount(dist + 1, dist + x, 1, ans);
            }
            else if(abs(i-x) < abs(i-y))
            {
                int p = ((x + y) / 2) + 1 + (i-x);
                int dist = i-x + 1;
                updateCount(p-i, n-i-1, -1, ans);
                updateCount(dist, dist + (y-p), 1, ans);
                updateCount(dist + 1, dist + (n-y-1), 1, ans);
            }
            else if(abs(i-y) < abs(i-x))
            {
                int p = ((x + y - 1) / 2) - (y-i);
                int dist = y-i + 1;
                updateCount(i-p, i, -1, ans);
                updateCount(dist, dist + (p-x), 1, ans);
                updateCount(dist + 1, dist + x, 1, ans);
            }
        }
        
        ans.erase(ans.begin());
        ans.erase(prev(ans.end()));
        
        for(int i = 1; i <= n; i++)
            ans[i] += ans[i-1];
        
        return ans;
    }
};
