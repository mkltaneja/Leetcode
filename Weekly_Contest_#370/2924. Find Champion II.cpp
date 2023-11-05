class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) 
    {
        vector<int> inDeg(n);
        for(vector<int> &e : edges)
            inDeg[e[1]]++;
        
        int ans = -1;
        for(int i = 0; i < n; i++)
        {
            if(inDeg[i] == 0)
            {
                if(ans == -1)
                    ans = i;
                else return -1;
            }
        }
        
        return ans;
    }
};
