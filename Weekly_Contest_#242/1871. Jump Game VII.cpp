
// APPROACH 1 (BFS) --> O(n^2)
// TLE

bool canReach(string s, int minJump, int maxJump)
{
    if (s[s.size() - 1] == '1')
        return false;
    queue<int> que;
    que.push(0);
    vector<bool> vis(s.size());
    while(!que.empty())
    {
        int j = que.front();
        que.pop();
        if(j == s.size()-1) return true;
        for(int i = j+minJump; i < s.size() && i <= j+maxJump; i++)
            if(s[i] == '0' && !vis[i])
                vis[i] = true, que.push(i);
    }
    return false;
}