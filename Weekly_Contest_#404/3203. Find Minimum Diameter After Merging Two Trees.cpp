
// Time Complexity = O(V + E)
// Space Complexity = O(V)

class Solution {
public:
    
    int getDiaByKahnAlgo(vector<vector<int>> &edges)
    {
        int n = edges.size() + 1;
        int dia = 0;
        vector<int> maxb(n, 0);
        vector<int> deg(n, 0);
        vector<vector<int>> gp(n);
        for(vector<int> &e : edges)
        {
            deg[e[0]]++;
            deg[e[1]]++;
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        queue<int> que;
        for(int i = 0; i < n; i++)
            if(deg[i] == 1)
                que.push(i);
        
        int lvl = 0;
        while(!que.empty())
        {
            int sz = que.size();
            while(sz--)
            {
                int u = que.front();
                que.pop();

                for(int v : gp[u])
                {
                    if(--deg[v] == 1)
                        que.push(v);
                    dia = max(dia, maxb[v] + (lvl + 1));
                    maxb[v] = max(maxb[v], lvl + 1);
                }
            }
            lvl++;
        }
        return dia;
    }
    
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2)
    {
        int dia1 = getDiaByKahnAlgo(edges1);
        int dia2 = getDiaByKahnAlgo(edges2);
        
        int x = (dia1 + 1) / 2;
        int y = (dia2 + 1) / 2;
        
        return max({dia1, dia2, x + y + 1});
    }
};
