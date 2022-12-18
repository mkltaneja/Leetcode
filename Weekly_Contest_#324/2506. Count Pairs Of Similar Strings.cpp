
// APPROACH 1 (Using set)

class Solution {
public:
    int similarPairs(vector<string>& words) 
    {
        unordered_map<string,int> mp;
        for(string &s : words)
        {
            string tmp = "";
            unordered_set<char> st;
            for(char &c : s)
            {
                if(st.count(c)) continue;
                st.insert(c);
                tmp += c;
            }
            sort(tmp.begin(), tmp.end());
            mp[tmp]++;
        }
        
        int ans = 0;
        for(auto &p : mp)
            ans += (p.second * (p.second-1))/2;
        
        return ans;
    }
};

// APPROACH 2 (Using Bits)  [OPTIMIZED]

class Solution {
public:
    int similarPairs(vector<string>& words) 
    {
        unordered_map<int,int> mp;
        int ans = 0;
        for(string &word : words)
        {
            int x = 0;
            for(char &c : word)
                x |= (1 << (c-'a'));
            ans += mp[x]++;
        }
        
        return ans;
    }
};
