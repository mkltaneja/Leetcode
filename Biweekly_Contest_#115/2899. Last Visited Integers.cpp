class Solution {
public:
    vector<int> lastVisitedIntegers(vector<string>& words) 
    {
        vector<int> ints, ans;
        for(int i = 0; i < words.size(); )
        {
            int j = ints.size()-1, pi = i;
            while(i < words.size() && words[i] == "prev")
            {
                if(j == -1) ans.push_back(-1);
                else ans.push_back(ints[j--]);
                i++;
            }
            if(i == pi)
                ints.push_back(stoi(words[i++]));
        }
        return ans;
    }
};
