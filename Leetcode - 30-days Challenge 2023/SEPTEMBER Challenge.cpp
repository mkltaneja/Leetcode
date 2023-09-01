
// DAY 1 ()====================================================================================================

vector<int> countBits(int n) 
{
    vector<int> ans(n+1, 0);
    
    if(n == 0) return ans;
    
    ans[1] = 1;
    int start = 0, end = 0, itr = 0, time = 0;
    for(int x = 2; x <= n; x++)
    {
        if((x & (x - 1)) == 0)
        {
            start = x / 2;
            itr = start;
            end = x - 1;
            time = 0;
        }
        ans[x] = ans[itr++] + time;
        if(itr == end+1)
        {
            itr = start;
            time++;
        }
    }

    return ans;
}
