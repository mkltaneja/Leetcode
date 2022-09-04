
int mostBooked(int n, vector<vector<int>>& meetings) 
{
    sort(meetings.begin(), meetings.end());
    priority_queue<pair<long,int>, vector<pair<long,int>>, greater<pair<long,int>>> tpq;
    priority_queue<long, vector<long>, greater<long>> rpq;
    for(int i = 0; i < n; i++)
        rpq.push(i);

    vector<int> cnt(n);

    for(vector<int> v : meetings)
    {
        while(!tpq.empty() && tpq.top().first <= v[0])
        {
            rpq.push(tpq.top().second);
            tpq.pop();
        }
        if(rpq.empty()) 
        {
            auto tp = tpq.top();
            tpq.pop();
            tpq.push({v[1] + (tp.first-v[0]), tp.second});
            cnt[tp.second]++;
        }
        else 
        {
            tpq.push({v[1], rpq.top()});
            cnt[rpq.top()]++;
            rpq.pop();
        }
    }

    int mxi = 0;
    for(int i = 0; i < n; i++)
        if(cnt[i] > cnt[mxi])
            mxi = i;

    return mxi;
}
