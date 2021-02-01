// DAY 1 (Number of 1 Bits)================================================================

int hammingWeight(uint32_t n) 
{
    int cnt = 0;
    while(n)
    {
        cnt++;
        n &= (n-1);
    }
    return cnt;
}