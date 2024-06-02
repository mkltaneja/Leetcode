
// Time Complexity = O(n*26 + n)
// Time Complexity = O(3*n)

class Solution {
public:
    string clearStars(string s) 
    {
        int n = s.size();
        vector<int> take(n, 1);
        vector<vector<int>> pos(26);
        string ans = "";
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '*')
            {
                for(int j = 0; j < 26; j++)
                {
                    if(pos[j].size())
                    {
                        take[pos[j].back()] = 0;
                        pos[j].pop_back();
                        break;
                    }
                }
                take[i] = 0;
            }
            else
                pos[s[i]-'a'].push_back(i);
        }
        
        for(int i = 0; i < n; i++)
            if(take[i])
                ans += s[i];
        return ans;
    }
};
