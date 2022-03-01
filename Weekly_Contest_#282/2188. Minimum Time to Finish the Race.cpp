int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) 
{
    int n = tires.size();
    int maxtlen = 33;
    vector<long> mnt(maxtlen, INT_MAX);
    for(auto v : tires)
    {
        long f = v[0];
        long r = v[1];
        long tott = 0;
        for(int i = 1; i < maxtlen && f <= INT_MAX; i++)
        {
            tott += f;
            mnt[i] = min(mnt[i], tott);
            f *= r;
        }
    }

    vector<long> dp(numLaps+1, INT_MAX);
    dp[0] = -changeTime;
    for(int i = 1; i <= numLaps; i++)
        for(int j = 1; j <= i && j < maxtlen; j++)
            dp[i] = min(dp[i], dp[i-j] + mnt[j] + changeTime);

    return dp[numLaps];
}
