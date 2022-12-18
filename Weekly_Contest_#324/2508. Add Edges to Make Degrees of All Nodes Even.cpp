class Solution {
public:
    
    bool isPossible(int n, vector<vector<int>>& edges) 
    {
        vector<unordered_set<int>> gp(n+1);
        for(vector<int> &e : edges)
        {
            gp[e[0]].insert(e[1]);
            gp[e[1]].insert(e[0]);
        }
        
        vector<int> odds;
        for(int i = 1; i <= n; i++)
            if(gp[i].size()&1)
                odds.push_back(i);
        
        if(odds.size() == 0) return true;
        if(odds.size() == 2)
        {
            for(int i = 1; i <= n; i++)
                if(!gp[i].count(odds[0]) && !gp[i].count(odds[1]))
                    return true;
            return false;
        }
        if(odds.size() == 4)
        {
            int a = odds[0], b = odds[1], c = odds[2], d = odds[3];
            return ((!gp[a].count(b) && !gp[c].count(d)) || 
                    (!gp[a].count(c) && !gp[b].count(d)) || 
                    (!gp[a].count(d) && !gp[b].count(c)));
        }
        
        return false;
    }
};
