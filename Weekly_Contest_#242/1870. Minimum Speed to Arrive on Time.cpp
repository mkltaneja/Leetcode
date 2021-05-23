
int minSpeedOnTime(vector<int> &dist, double hour)
{
    int ss = 1, es = 1e7 + 1, ms;
    while (ss < es)
    {
        ms = (ss + es) >> 1;
        double time = 0;
        int i = 0;
        for (; i < dist.size() - 1; i++)
            time += ceil(1.0 * dist[i] / ms);
        time += (1.0 * dist[i] / ms);
        if (time > hour)
            ss = ms + 1;
        else
            es = ms;
    }

    if (es == 1e7 + 1)
        return -1;
    return es;
}