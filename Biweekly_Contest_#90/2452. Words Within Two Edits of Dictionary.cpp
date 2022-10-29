class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) 
    {
        int n = queries.size(), m = dictionary.size();
        vector<string> ans;
        for(int i = 0; i < n; i++)
        {
            string s = queries[i];
            for(int j = 0; j < m; j++)
            {
                int edits = 0;
                int x = 0, y = 0;
                while(x < s.size() && edits < 3)
                {
                    if(s[x++] != dictionary[j][y++]) edits++;
                }
                if(edits < 3)
                {
                    ans.push_back(s);
                    break;
                }
            }
        }
        
        return ans;
    }
};
