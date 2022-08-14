
// APPROACH 1 (Using DFS) -> time = >O(n!) [n = no. of digits]

int vis = 0;
int ans = 0;
int mx = 0;

void dfs(long x)
{
    if(x > mx) return;
    ans++;
    for(int i = 0; i < 10; i++)
    {
        if(vis & (1 << i)) continue;
        vis ^= (1 << i);
        dfs(x*10 + i);
        vis ^= (1 << i);
    }
}

int countSpecialNumbers(int n) 
{
    mx = n;
    for(int i = 1; i < 10; i++)
    {
        vis ^= (1 << i);
        dfs(i);
        vis ^= (1 << i);
    }

    return ans;
}

// APPROACH 2 (Using permutation and combination concepts) -> time = O(n*n) [n = no. of digits]

int countSpecialNumbers(int n) 
{
    vector<int> dig;
    int digs = 0;
    int tmp = n;
    while(tmp)
    {
        dig.push_back(tmp % 10);
        digs++;
        tmp /= 10;
    }
    reverse(dig.begin(), dig.end());

    int ans = 0;
    for(int i = 0; i < digs-1; i++)
    {
        int curr = 9;
        for(int j = 0; j < i; j++)
            curr *= (9 - j);
        ans += curr;
    }

    vector<int> vis(10,0);
    for(int i = 0; i < digs; i++)
    {
        int small = 0;
        for(int x = 0; x < dig[i]; x++)
            if(!vis[x])
                small++;
        small -= (i == 0);

        int fix = 10 - i - 1, curr = 1;
        for(int j = i+1; j < digs; j++)
            curr *= fix, fix--;
        ans += small * curr;

        if(!vis[dig[i]]) vis[dig[i]] = 1;
        else break;
    }

    int used = 0;
    bool amAns = true;
    for(int x : dig)
    {
        if(used & (1 << x))
        {
            amAns = false;
            break;
        }
        used ^= (1 << x);
    }

    ans += amAns;

    return ans;
}
