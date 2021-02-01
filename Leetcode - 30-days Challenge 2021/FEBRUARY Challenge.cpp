// DAY 1 (Number of 1 Bits)================================================================

// in C++
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

// in Java
// you need to treat n as an unsigned value
public int hammingWeight(int n) {
    int cnt = 0;
    if((n & (1<<31)) != 0)
    {        
        n ^= (1<<31);
        cnt++;
    }
    System.out.println(n);
    while(n>0)
    {
        cnt++;
        n &= (n-1);
    }
    return cnt;
}
// OR
public int hammingWeight(int n) {
    return Integer.bitCount(n);
}