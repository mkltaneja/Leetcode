class Solution {
public:
    int hardestWorker(int n, vector<vector<int>>& logs) 
    {
        int last = 0;
        int mx = 0;
        int ans = -1;
        for(vector<int> &v : logs)
        {
            if(v[1] - last >= mx)
            {
                mx = v[1] - last;
                ans = v[0];
            }
            else if(v[1] - last == mx)
                ans = min(ans, v[0]);
            last = v[1];
        }
        
        return ans;
    }
};
