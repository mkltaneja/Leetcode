
// Time Complexity = O(n * m * max(n, m) * sqrt(num))

class Solution {
public:
    
    bool isPrime(int x)
    {
        if(x/10 == 0) return false;
        for(int i = 2; i*i <= x; i++)
            if(x % i == 0)
                return false;
        return true;
    }
    
    int mostFrequentPrime(vector<vector<int>>& mat) 
    {
        int n = mat.size(), m = mat[0].size();
        unordered_map<int,int> mp;
        int dir[8][2] = {{1,0}, {0,1}, {-1,0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                for(int d = 0; d < 8; d++)
                {
                    int x = i, y = j;
                    int num = 0;
                    while(x < n && y < m && x >= 0 && y >= 0)
                    {
                        num = num*10 + mat[x][y];
                        if(isPrime(num))
                            mp[num]++;
                        x += dir[d][0], y += dir[d][1];
                    }
                }
            }
        }
        
        int ans = -1, mf = 0;
        for(auto p : mp)
        {
            if(p.second > mf)
                mf = p.second, ans = p.first;
            else if(p.second == mf)
                ans = max(ans, p.first);
        }
        
        return ans;
    }
};
