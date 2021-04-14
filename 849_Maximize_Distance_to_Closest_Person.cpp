
int maxDistToClosest(vector<int> &seats)
{
    int n = seats.size();
    int i = 0;
    while (!seats[i])
        i++;
    int ans = i;
    int pi = i;
    while (i < n)
    {
        if (seats[i])
        {
            ans = max(ans, ((i - pi - 1) + 1) / 2);
            pi = i;
        }
        // cout<<seats[i]<<" "<<ans<<endl;
        i++;
    }
    ans = max(ans, (i - pi - 1));
    return ans;
}