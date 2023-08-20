class Solution {
public:
    int minimumSum(int n, int k) 
    {
        int sum = 0, x = 0;
        unordered_set<int> st;
        while(n)
        {
            if(st.count(k - ++x))
                continue;
            sum += x;
            n--;
            st.insert(x);
        }
        
        return sum;
    }
};
