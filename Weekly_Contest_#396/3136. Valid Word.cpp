
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    bool isValid(string word) 
    {
        if (word.length() < 3)
            return false;

        bool hasVowel = false;
        bool hasConsonant = false;
        int cond1 = 0, cond2 = 0, cond3 = 0;

        for (char ch : word) 
        {
            if (isalpha(ch)) 
            {
                if (tolower(ch) == 'a' || tolower(ch) == 'e' || tolower(ch) == 'i' || tolower(ch) == 'o' || tolower(ch) == 'u')
                    hasVowel = true;
                else
                    hasConsonant = true;
            }
            else if(!isdigit(ch))
                return false;
        }

        return hasVowel && hasConsonant;
    }
};
