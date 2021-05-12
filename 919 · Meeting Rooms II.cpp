
int minMeetingRooms(vector<Interval> &intervals)
{
    sort(intervals.begin(), intervals.end(), [](Interval &a, Interval &b)
         { return (a.start == b.start) ? (a.end < b.end) : (a.start < b.start); });

    int rooms = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < intervals.size(); i++)
    {
        pq.push(intervals[i].end);
        if (intervals[i].start < pq.top())
            rooms++;
        else
            pq.pop();
    }

    return rooms;
}