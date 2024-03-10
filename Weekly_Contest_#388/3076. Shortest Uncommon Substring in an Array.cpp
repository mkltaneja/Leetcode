
// Time Complexity = O(2*n*m*m)
// Space Complexity = O(n*m*m + n)

class Solution {
public:
    
    string MX = string(25, 'z');
    vector<string> shortestSubstrings(vector<string>& arr) 
    {
        unordered_map<string,unordered_set<int>> mp;
        int x = 0;
        vector<string> ans;
        for(string s : arr)
        {
            for(int i = 0; i < s.size(); i++)
            {
                string curr = "";
                for(int j = i; j < s.size(); j++)
                {
                    curr += s[j];
                    mp[curr].insert(x);
                }
            }
            x++;
        }

        for(string s : arr)
        {
            string maxStr = MX;
            for(int i = 0; i < s.size(); i++)
            {
                string curr = "";
                for(int j = i; j < s.size(); j++)
                {
                    curr += s[j];
                    if(mp[curr].size() == 1 && (curr.size() < maxStr.size() || (curr.size() == maxStr.size() && curr < maxStr)))
                        maxStr = curr;
                }
            }
            if(maxStr == MX)
                ans.push_back("");
            else
                ans.push_back(maxStr);
        }
        
        return ans;
    }
};
