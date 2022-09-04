
#define ll long long
int maximumRobots(vector<int>& mx, vector<int>& sums, long long budget) 
{
    int n = mx.size();
    deque<ll> que;

    ll j = 0;
    ll sum = 0;
    ll ans = 0;
    for(ll i = 0; i < n; i++)
    {
        while(!que.empty() && que.back() <= mx[i])
        {
            que.pop_back();
        }
        que.push_back(mx[i]);
        sum += sums[i];

        ll curr = que.front() + (i-j+1)*sum;

        while(curr > budget)
        {
            sum -= sums[j];
            if(que.front() == mx[j])
                que.pop_front();
            j++;
            curr = que.front() + (i-j+1)*sum;
        }

        ans = max(ans, i-j+1);
    }

    return ans;
}
