
int mod = 1e9 + 7;
int numberOfWays(int st, int end, int k) 
{
    int diff = abs(end-st);
    if((diff & 1) != (k & 1) || k < diff)
        return 0;

    vector<long> curr(2001, 0);
    curr[1000] = 1;
    for(int i = 0; i < k; i++)
    {
        vector<long> nxt(2001, 0);
        for(int j = 0; j < 2000; j++)
        {
            if(j) nxt[j-1] = (nxt[j-1] + curr[j]) % mod;
            nxt[j+1] = (nxt[j+1] + curr[j]) % mod;
        }
        curr = nxt;
    }

    return curr[1000 + diff];
}
