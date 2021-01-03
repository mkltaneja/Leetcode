
int countPairs(vector<int> &arr)
{
    unordered_map<int, int> m;
    for (int i : arr)
        m[i]++;
    vector<int> pow2(22);
    int x = 1, i = 0;
    while (i < 22)
    {
        pow2[i++] = x;
        x *= 2;
    }

    long ans = 0;
    for (int num : arr)
    {
        int count = 0;
        // cout<<num<<" --> ";
        for (i = 0; i < 22; i++)
        {
            if (num <= pow2[i])
            {
                int num1 = pow2[i] - num;
                if (m.find(num1) != m.end())
                {
                    ans += m[num1];
                    if (num == num1)
                        ans--;
                    // cout<<num1<<", ";
                }
                // cout<<pow2[i]<<", "<<pow2[i]-num<<" \n ";
            }
        }
        // m1[num1] = count;
        // cout<<"ANSWER: \n"<<count<<endl;
    }
    ans /= 2;
    // cout<<endl;
    return ans % (int)(1e9 + 7);
}