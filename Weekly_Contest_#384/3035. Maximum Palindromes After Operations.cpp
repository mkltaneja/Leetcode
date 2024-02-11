
// APPROACH 1 (Brute Force)

// Time Complexity = O(n + n*logn + n * (26*log26 + m*26 + 26))
// Space Complexity = O(n + 26)

class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) 
    {
        int n = words.size();
        int ans = 0;
        vector<int> freq(26);
        vector<int> lens;
        for(string word : words)
        {
            for(char c : word)
                freq[c-'a']++;
            lens.push_back(word.size());
        }
        sort(lens.begin(), lens.end());
        
        for(int len : lens)
        {
            sort(freq.rbegin(), freq.rend());
            while(len > 1)
            {
                int go = 0;
                for(int i = 0; i < 26 && len > 1; i++)
                {
                    if(freq[i] <= 1) continue;
                    len -= 2;
                    freq[i] -= 2;
                    go = 1;
                }
                if(!go) break;
            }
            if(len > 1) return ans;
            
            int evenPos = -1;
            for(int i = 0; i < 26 && len; i++)
            {
                if(freq[i] & 1)
                {
                    freq[i]--;
                    len--;
                }
                else evenPos = i;
            }
            if(len)
            {
                if(evenPos == -1) return ans;
                freq[evenPos]--;
            }
            ans++;
        }
        
        return ans;
    }
};


// APPROACH 2 (Greedily)

// Time Complexity = O(2*n + n*logn + 26)
// Space Complexity = O(n + 26)

class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) 
    {
        int n = words.size();
        int totalPals = 0;
        vector<int> freq(26);
        vector<int> lens;
        int canSwaps = 0;
        for(string word : words)
        {
            for(char c : word)
                freq[c-'a']++;
            lens.push_back(word.size());
        }
        
        for(int i = 0; i < 26; i++)
            canSwaps += freq[i] / 2;
        
        sort(lens.begin(), lens.end());
                
        for(int len : lens)
        {
            int needSwaps = len / 2;
            if(canSwaps - needSwaps >= 0)
            {
                canSwaps -= needSwaps;
                totalPals++;
            }
        }
        
        return totalPals;
    }
};
