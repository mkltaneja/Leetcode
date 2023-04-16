class Graph {
public:

    #define ll long long
    #define f first
    #define s second
    
    int n;
    vector<vector<vector<int>>> gp;
    Graph(int n, vector<vector<int>>& edges) 
    {
        this->n = n;
        this->gp.resize(n);
        for(auto e : edges)
            gp[e[0]].push_back({e[1], e[2]});
    }
    
    void addEdge(vector<int> edge) 
    {
        gp[edge[0]].push_back({edge[1], edge[2]});
    }
    
    int shortestPath(int node1, int node2) 
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> que;
        que.push({0, node1});
        vector<int> mindist(n, INT_MAX);
        while(!que.empty())
        {
            ll x = que.top().f;
            int u = que.top().s;
            que.pop();
            
            if(u == node2)
                return x;
            
            for(vector<int> &v : gp[u])
            {
                if(x + v[1] < mindist[v[0]])
                {
                    mindist[v[0]] = x + v[1];
                    que.push({x + v[1], v[0]});
                }
            }
        }
        
        return -1;
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
