int k = 3;
int singleNumber(vector<int> &nums)
{
    int ans = 0;
    for (int i = 0; i < 32; i++)
    {
        int countbits = 0;
        int mask = (1 << i);
        for (int ele : nums)
            if (ele & mask)
                countbits++;
        // cout<<countbits<<endl;

        if (countbits % k != 0)
            ans |= mask;
    }
    return ans;
}