
int minimumRecolors(string blocks, int k) 
{
    int n = blocks.size();
    int w = 0;
    int ans = INT_MAX;
    for(int i = 0; i < n; i++)
    {
        w += blocks[i] == 'W';
        if(i >= k) w -= blocks[i-k] == 'W';
        if(i >= k-1) ans = min(ans, w);
    }

    return ans;
}
