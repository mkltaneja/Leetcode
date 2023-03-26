class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) 
    {
        int n = coins.size();
        
        vector<vector<int>> gp(n);
        vector<int> deg(n);
        queue<int> que;
        vector<int> childCoins;
        vector<bool> isIncluded(n, true);

        for(vector<int> &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
            deg[e[0]]++;
            deg[e[1]]++;
        }
        
        for(int i = 0; i < n; i++)
        {
            if(deg[i] == 1 && coins[i] == 0)
            {
                que.push(i);
                isIncluded[i] = false;
            }
        }
        while(!que.empty())
        {
            int u = que.front();
            que.pop();
            for(int v : gp[u])
            {
                if(--deg[v] == 1 && coins[v] == 0)
                {
                    que.push(v);
                    isIncluded[v] = false;
                }
            }
        }
        
        for(int i = 0; i < n; i++)
        {
            if(deg[i] == 1 && coins[i] == 1)
            {
                childCoins.push_back(i);
                isIncluded[i] = false;
            }
        }
        
        for(int u : childCoins)
            for(int v : gp[u])
                if(--deg[v] == 1)
                    isIncluded[v] = false;
        
        int ans = 0;
        for(vector<int> &e : edges)
            if(isIncluded[e[0]] && isIncluded[e[1]])
                ans += 2;
        
        return ans;
    }
};
