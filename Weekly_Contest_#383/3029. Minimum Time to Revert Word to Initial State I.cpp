
// APPROACH 1 (Using set)

// Time Complexity = O(n^2 + n/k)
// Space Complexity = O(n)

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) 
    {
        int n = word.size();
        
        unordered_set<int> lens;
        int i = 0, j = n-1;
        for(; i < n-1; i++, j--)
        {
            string s1 = word.substr(0, i+1);
            string s2 = word.substr(j);
            if(s1 == s2)
                lens.insert(i+1);
        }
        
        int cnt = 0;
        while(n > 0)
        {
            n -= k;
            cnt++;
            if(lens.count(n))
                return cnt;
        }
        
        return cnt;
    }
};

// APPROACH 2 (Checking in a single loop without set)

// Time Complexity = O(n^2)
// Space Complexity = O(1)

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) 
    {
        int n = word.size();
        
        for(int i = k; i < n; i += k)
        {
            string s1 = word.substr(0, n-i);
            string s2 = word.substr(i);
            if(s1 == s2)
                return i / k;
        }
        
        return (n + k - 1) / k;;
    }
};
