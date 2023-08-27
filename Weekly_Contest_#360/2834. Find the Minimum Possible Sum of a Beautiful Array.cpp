class Solution {
public:
    long long minimumPossibleSum(int n, int target) 
    {
        long long x = 1, sum = 0;
        unordered_set<long long> st;
        while(n)
        {
            if(st.count(target - x))
            {
                x++;
                continue;
            }
            st.insert(x);
            sum += x++;
            n--;
        }
        return sum;
    }
};
