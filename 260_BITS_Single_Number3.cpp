vector<int> singleNumber(vector<int> &nums)
{
    int nre = 0;
    for (int ele : nums)
        nre ^= ele;
    int lsb = (nre & -nre);
    cout << lsb << endl;
    int a = 0;
    int b = 0;
    for (int ele : nums)
    {
        if ((lsb & ele) == 0)
            a ^= ele;
        else
            b ^= ele;
        // cout<<a<<" "<<b<<endl;
    }
    return {a, b};
}