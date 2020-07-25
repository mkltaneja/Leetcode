#define mod (int)1e9 + 7

// O(n^2)
// TLE
int numOfSubarrays(vector<int> &arr)
{
    int n = arr.size();

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += arr[j];
            if (sum & 1)
                count = (count % mod + 1) % mod;
        }
    }
    return count;
}

/////////////OR///////////////////////////////////

// O(n)
int numOfSubarrays(vector<int> &arr)
{
    unsigned int count = 0, odd = 0, even = 1, sum = 0;
    for (int i : arr)
    {
        sum += i;
        if (sum & 1)
        {
            count += even;
            odd++;
        }
        else
        {
            count += odd;
            even++;
        }
        count %= mod;
    }
    return count;
}