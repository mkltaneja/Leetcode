long long minimumTime(vector<int>& time, int totalTrips) 
{
    sort(time.begin(), time.end());
    long long st = 1, end = (long long)time[0]*totalTrips;

    while(st < end)
    {
        long long mid = st + ((end - st)>>1);
        long long ttrips = 0;
        for(long long x : time)
            ttrips += mid/x;
        if(ttrips < totalTrips) st = mid + 1;
        else end = mid;
    }

    return st;
}
