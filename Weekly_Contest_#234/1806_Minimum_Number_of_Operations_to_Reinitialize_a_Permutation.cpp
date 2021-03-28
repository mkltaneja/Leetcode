
// METHOD 1 (Brute Force) --> O(n^2)

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

// METHOD 2 (Inverse Method) --> O(n)

int reinitializePermutation(int n)
{
    vector<int> perm(n), arr(n);
    for (int i = 0; i < n; i++)
        perm[i] = i;
    for (int i = 0; i < n; i++)
        arr[i] = (i & 1) ? perm[n / 2 + i / 2] : perm[i / 2];
    int ans = 0;
    int x = 1;
    while (1)
    {
        x = arr[x];
        ans++;
        if (x == 1)
            break;
    }
    return ans;
}