bool isPowerOfFour(int num)
{
    if (num == 1)
        return true;
    if (num % 2 != 0 || num <= 0 || (num & (num - 1)) != 0)    //return false if not the power of two 
        return false;

    int counttz = 0;
    while (num != 1)
    {
        num >>= 1;
        counttz++;
    }
    return !(counttz & 1);    //return true if count of trailing zeroes in binary is even
}