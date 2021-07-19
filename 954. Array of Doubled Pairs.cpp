
bool canReorderDoubled(vector<int> &arr)
{
    sort(arr.begin(), arr.end());
    unordered_map<int, int> m;
    for (int x : arr)
        m[x]++;
    for (int x : arr)
    {
        if (m[x] == 0)
            continue;
        if (x < 0)
        {
            if (-x & 1)
                return false;
            else if (m[x / 2] == 0)
                return false;
            if (--m[x] == 0)
                m.erase(x);
            if (--m[x / 2] == 0)
                m.erase(x / 2);
        }
        else
        {
            if (m[2 * x] == 0)
                return false;
            if (--m[x] == 0)
                m.erase(x);
            if (--m[2 * x] == 0)
                m.erase(2 * x);
        }
    }
    return true;
}