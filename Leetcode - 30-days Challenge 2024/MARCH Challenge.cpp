
// DAY 1 (2864. Maximum Odd Binary Number)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

string maximumOddBinaryNumber(string s)
{
    int size = s.size();
    int lastOnePos = -1;
    for(int p1 = 0, p2 = 0; p1 < size; p1++)
    {
        if(s[p1] == '1')
        {
            lastOnePos = p2;
            swap(s[p1], s[p2++]);
        }
    }
    if(lastOnePos != -1)
        swap(s[lastOnePos], s[size-1]);
    return s;
}
