
// APPROACH 1 (By Counting indegree) --> Time = O(n + n^2), Space = O(n)

class Solution {
public:
    int findChampion(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        vector<int> inDeg(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(i != j && grid[i][j])
                    inDeg[j]++;
        for(int i = 0; i < n; i++)
            if(inDeg[i] == 0)
                return i;
        return -1;
    }
};

// APPROACH 2 (Finding answer linearly) --> Time = O(n), Space = O(1)

class Solution {
public:
    int findChampion(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        int ans = 0;
        for(int i = 1; i < n; i++)
            if(grid[ans][i] == 0)
                ans = i;
        return ans;
    }
};
