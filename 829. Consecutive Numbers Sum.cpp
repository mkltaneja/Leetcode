
int consecutiveNumbersSum(int N) 
{
    int ans = 0;
    int limit = sqrt(2*N);
    for(int k = 1; k <= limit; k++) // k is the length of series
        if(((N - (k*(k-1))/2) % k) == 0) 
            ans++;
    return ans;
}