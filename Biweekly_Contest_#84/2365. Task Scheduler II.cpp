
// APPROACH 1 (Using 2 hashmap2)

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

// APPROACH 2 (Using 1 hashmap)

long long taskSchedulerII(vector<int> &tasks, int space)
{
    unordered_map<int, long long> last;
    long long days = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        days++;
        if (last.count(tasks[i]))
            days = max(days, last[tasks[i]] + space + 1);

        last[tasks[i]] = days;
    }

    return days;
}