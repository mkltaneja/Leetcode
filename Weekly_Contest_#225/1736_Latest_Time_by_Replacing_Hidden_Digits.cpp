// APPROACH 1

string maximumTime(string time)
{
    int max[5] = {2, 3, 0, 5, 9};
    for (int i = 0; i < time.size(); i++)
    {
        if (time[i] == '?')
        {
            if (i == 0)
            {
                if (time[1] == '?' || (time[1] >= '0' && time[1] <= '3'))
                    time[i] = '2';
                else
                    time[i] = '1';
            }
            else if (i == 1)
            {
                if (time[0] == '2')
                    time[i] = '3';
                else
                    time[i] = '9';
            }
            else
                time[i] = max[i] + '0';
        }
    }
    return time;
}

// APPROACH 2

bool maxtime(char c, int x)
{
    return (c == '?') || (x == c - '0');
}

string maximumTime(string time)
{
    for (int i = 23; i >= 0; i--)
    {
        if (maxtime(time[0], i / 10) && maxtime(time[1], i % 10))
        {
            time[0] = (i / 10) + '0';
            time[1] = (i % 10) + '0';
            break;
        }
    }
    if (time[3] == '?')
        time[3] = '5';
    if (time[4] == '?')
        time[4] = '9';
    return time;
}