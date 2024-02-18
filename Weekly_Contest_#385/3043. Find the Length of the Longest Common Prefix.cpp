
// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) 
    {
        int n = arr1.size(), m = arr2.size();
        unordered_set<string> st;
        
        for(int x : arr1)
        {
            string y = to_string(x);
            string tmp = "";
            for(char c : y)
            {
                tmp += c;
                st.insert(tmp);
            }
        }
        int ans = 0;
        for(int x : arr2)
        {
            string y = to_string(x);
            string tmp = "";
            for(char c : y)
            {
                tmp += c;
                if(st.count(tmp))
                    ans = max(ans, (int)tmp.size());
            }
        }
        
        return ans;
    }
};
