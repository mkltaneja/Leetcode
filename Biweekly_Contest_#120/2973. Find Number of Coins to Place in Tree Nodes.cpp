
// Time = O(n^3), Space = O(n^2)

class Solution {
public:
    
    #define ll long long
    
    vector<vector<ll>> dfs(int u, int p, vector<vector<int>> &gp, vector<int> &cost, vector<ll> &coin)
    {
        ll csize = 1;
        vector<ll> pos, neg;
        if(cost[u] > 0)
            pos.push_back(cost[u]);
        else
            neg.push_back(cost[u]);
        for(int v : gp[u])
        {
            if(v == p) continue;
            vector<vector<ll>> cans = dfs(v, u, gp, cost, coin);
            vector<ll> cpos = cans[0];
            vector<ll> cneg = cans[1];
            csize += cans[2][0];
            
            pos.insert(pos.end(), cpos.begin(), cpos.end());
            neg.insert(neg.end(), cneg.begin(), cneg.end());
            
        }
        
        sort(pos.rbegin(), pos.rend());
        sort(neg.begin(), neg.end());
        if(pos.size() > 3)
            pos.erase(pos.begin()+3, pos.end());
        if(neg.size() > 2)
            neg.erase(neg.begin()+2, neg.end());
        
        if(csize <= 2)
        {
            coin[u] = 1;
            while(pos.size() < 3)
                pos.push_back(0);
            while(neg.size() < 2)
                neg.push_back(0);
        }
        else 
        {
            if(pos[0] && pos[1] && pos[2])
            {
                coin[u] = max(coin[u], pos[0] * pos[1] * pos[2]);
                if(neg[0] && neg[1])
                    coin[u] = max(coin[u], pos[0] * neg[0] * neg[1]);
            }
            if(pos[0] && pos[1])
            {
                if(neg[0] && neg[1])
                    coin[u] = max(coin[u], pos[0] * neg[0] * neg[1]);
                else coin[u] = max(coin[u], 0ll);
            }
            if(pos[0])
            {
                if(neg[0] && neg[1])
                    coin[u] = max(coin[u], pos[0] * neg[0] * neg[1]);
            }
            coin[u] = max(coin[u], 0ll);
        }
        
        return {pos, neg, {csize}};
    }
    
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) 
    {
        int n = cost.size();
        vector<ll> coin(n, -1);
        vector<vector<int>> gp(n);
        for(auto &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        dfs(0, -1, gp, cost, coin);
        
        return coin;
    }
};
