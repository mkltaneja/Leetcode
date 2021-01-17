
int tupleSameProduct(vector<int> &nums)
{
    int n = nums.size(), count = 0;
    unordered_map<int, int> prods;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int prod = nums[i] * nums[j];
            ++prods[prod];
            // count += (cnt*(cnt-1))/2;
            // prods[prod]++;
        }
    }
    for (auto p : prods)
        count += (p.second * (p.second - 1)) / 2;
    return count * 8;
}