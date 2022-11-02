// DAY 1 (1706. Where Will the Ball Fall)===========================================================================

vector<int> findBall(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();

    vector<int> ans(m, -1);
    for(int x = 0; x < m; x++)
    {
        int i = 0, j = x;
        while(i < n)
        {
            if(grid[i][j] == 1 && (j+1 == m || grid[i][j+1] == -1)) break;
            if(grid[i][j] == -1 && (j-1 == -1 || grid[i][j-1] == 1)) break;
            j += grid[i++][j];
        }
        if(i == n) ans[x] = j;
    }

    return ans;
}

// DAY 2 (433. Minimum Genetic Mutation)=================================================================================

int minMutation(string start, string end, vector<string>& bank) 
{
    if(start == end) return 0;

    unordered_set<string> st;
    for(string &s : bank)
        st.insert(s);

    queue<string> que;
    que.push(start);

    int lvl = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            string curr = que.front();
            que.pop();

            for(int i = 0; i < 8; i++)
            {
                for(char c : {'A', 'C', 'G', 'T'})
                {
                    if(c == curr[i]) continue;

                    string nxt = curr.substr(0,i) + c + curr.substr(i+1);
                    if(!st.count(nxt)) continue;
                    st.erase(nxt);

                    if(nxt == end) return lvl+1;

                    que.push(nxt);
                }
            }
        }
        lvl++;
    }

    return -1;
}
