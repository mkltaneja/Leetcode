// DAY 1 (344. Reverse String)=================================================================================================

void reverseString(vector<char>& s) 
{
    reverse(s.begin(), s.end());
}

// DAY 2 (680. Valid Palindrome II)=================================================================================================

bool ispal(string &s, int i, int j)
{
    while(i <= j && s[i] == s[j]) i++, j--;

    return i > j;
}

bool validPalindrome(string s) 
{
    int i = 0, j = s.size()-1;
    while(i <= j)
    {
        if(s[i] != s[j])
            return ispal(s, i+1, j) || ispal(s, i, j-1);
        i++, j--;
    }
    return true;
}
