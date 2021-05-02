// DAY 2 (Course Schedule 3)======================================================================

// APPROACH 1 (Subsequence) --> <O(2^n)
// TLE

int subseq(int i, int day, vector<vector<int>> &v)
{
    if (i == v.size())
        return 0;

    int ans = 0;
    if (day + v[i][0] <= v[i][1])
        ans = subseq(i + 1, day + v[i][0], v) + 1;
    ans = max(ans, subseq(i + 1, day, v));

    return ans;
}

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b) {
        return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1];
    });
    return subseq(0, 0, courses);
}

// APPROACH 2 (Greedy -- Taking the minimum durations to maximize course count) --> O(n*logn)
// METHOD 1
// AC

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b) {
        return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1];
    });

    priority_queue<int> pq;
    int day = 0;
    for (vector<int> v : courses)
    {
        int dur = v[0], lim = v[1];
        if (day + dur <= lim)
        {
            day += dur;
            pq.push(dur);
        }
        else if (!pq.empty() && pq.top() > dur)
        {
            day += dur - pq.top();
            pq.pop();
            pq.push(dur);
        }
    }
    return pq.size();
}

// METHOD 2 (Shorter version of METHOD 1)

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b) {
        return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1];
    });

    priority_queue<int> pq;
    int day = 0;
    for (vector<int> v : courses)
    {
        int dur = v[0], lim = v[1];
        day += dur;
        pq.push(dur);
        if (day > lim)
        {
            day -= pq.top();
            pq.pop();
        }
    }
    return pq.size();
}