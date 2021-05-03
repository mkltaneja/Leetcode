
vector<int> getModifiedArray(int length, vector<vector<int>> &updates)
{
    vector<int> arr(length, 0);
    for (auto v : updates)
    {
        int si = v[0], ei = v[1], inc = v[2];
        arr[si] += inc;
        if (ei + 1 < length)
            arr[ei + 1] -= inc;
    }
    for (int i = 1; i < length; i++)
        arr[i] += arr[i - 1];

    return arr;
}