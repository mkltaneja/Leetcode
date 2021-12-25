
int minimumRefill(vector<int> &plants, int cA, int cB)
{
    int ans = 0;
    int i = 0, j = plants.size() - 1;
    int ca = cA, cb = cB;

    while (i <= j)
    {
        if (i == j)
        {
            if (ca < plants[i] && cb < plants[j])
                ans++;
            break;
        }
        if (ca < plants[i])
        {
            ca = cA;
            ans++;
        }
        if (cb < plants[j])
        {
            cb = cB;
            ans++;
        }
        ca -= plants[i++];
        cb -= plants[j--];
    }

    return ans;
}