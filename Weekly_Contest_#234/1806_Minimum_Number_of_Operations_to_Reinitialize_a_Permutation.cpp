
int reinitializePermutation(int n)
{
    vector<int> perm(n), arr, temp;
    for (int i = 0; i < n; i++)
        perm[i] = i;
    arr = perm;
    temp = perm;
    int ans = 0;

    do
    {
        for (int i = 0; i < n; i++)
            arr[i] = (i & 1) ? temp[n / 2 + (i - 1) / 2] : temp[i / 2];
        ans++;
        temp = arr;
    } while (arr != perm);

    return ans;
}