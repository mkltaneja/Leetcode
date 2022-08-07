
int maximumGroups(vector<int> &grades)
{
    int ans = 0;
    long sum = 0, p = 2, i = 0;
    for (; i < grades.size(); i += p++)
        ans++;
    return ans;
}