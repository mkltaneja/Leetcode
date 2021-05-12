
bool canAttendMeetings(vector<Interval> &intervals)
{
    if (intervals.empty())
        return true;
    sort(intervals.begin(), intervals.end(), [](Interval &a, Interval &b)
         { return (a.start == b.start) ? (a.end < b.end) : (a.start < b.start); });
    for (int i = 0; i < intervals.size() - 1; i++)
        if (intervals[i + 1].start < intervals[i].end)
            return false;
    return true;
}