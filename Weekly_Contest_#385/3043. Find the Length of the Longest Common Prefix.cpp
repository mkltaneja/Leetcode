
// APPROACH 1 (Implementing with String)

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


// APPROACH 2 (Implementing with integer only) [OPTIMIZED]

// Time Complexity = O(n*m)
// Space Complexity = O(n)

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) 
    {
        int n = arr1.size(), m = arr2.size();
        unordered_set<int> st;
        
        for(int x : arr1)
            for(; x; x /= 10)
                st.insert(x);
        
        int ans = 0;
        for(int x : arr2)
        {
            for(; x > ans; x /= 10)
            {
                if(st.count(x))
                {
                    ans = x;
                    break;
                }
            }
        }
        
        return ans? to_string(ans).size() : 0;
    }
};
