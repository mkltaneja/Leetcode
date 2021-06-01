
vector<int> majorityElement(vector<int> &nums)
{
    int n = nums.size();
    int a, b;
    int cnt1 = 0, cnt2 = 0;
    for (int x : nums)
    {
        if (x == a)
            cnt1++;
        else if (x == b)
            cnt2++;
        else if (cnt1 == 0)
            a = x, cnt1 = 1;
        else if (cnt2 == 0)
            b = x, cnt2 = 1;
        else
            cnt1--, cnt2--;
    }
    cnt1 = 0, cnt2 = 0;
    for (int x : nums)
    {
        if (x == a)
            cnt1++;
        else if (x == b)
            cnt2++;
    }
    cout << a << " " << b << endl;
    cout << cnt1 << " " << cnt2 << endl;
    if (cnt1 > n / 3 && cnt2 > n / 3)
        return {a, b};
    if (cnt1 > n / 3)
        return {a};
    if (cnt2 > n / 3)
        return {b};
    return {};
}