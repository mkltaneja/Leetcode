
long long taskSchedulerII(vector<int> &tasks, int space)
{
    unordered_map<int, int> last;
    unordered_map<int, long long> breaks;
    long long tot = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        if (last.count(tasks[i]))
        {
            long long gaps = (i - last[tasks[i]] - 1) + (tot - breaks[tasks[i]]);
            if (gaps < space)
                tot += space - gaps;
        }

        last[tasks[i]] = i;
        breaks[tasks[i]] = tot;
    }

    return tot + tasks.size();
}