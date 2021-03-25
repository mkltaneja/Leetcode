// APPROACH 1 (Using Priority Queue) --> O(d[1])

int maximumScore(int a, int b, int c)
{
    priority_queue<int> pq;
    pq.push(a);
    pq.push(b);
    pq.push(c);

    int cnt = 0;
    while (pq.size() > 1)
    {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        // cout<<x<<" "<<y<<endl;
        if (x - 1 > 0)
            pq.push(x - 1);
        if (y - 1 > 0)
            pq.push(y - 1);

        cnt++;
    }
    return cnt;
}

// APPROACH 2 (Using array)  --> O(d[1])
int maximumScore(int a, int b, int c)
{
    int d[3] = {a, b, c};
    sort(d, d + 3);
    int cnt = 0;
    while (d[1])
    {
        cnt++;
        if (d[0])
            d[0]--;
        else
            d[1]--;
        d[2]--;
        sort(d, d + 3);
    }
    return cnt;
}