
// APPROACH 1 (Using set) --> time = O(2*n), space = O(n)

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

// APPROACH 2 (Mathematically) --> time = O(1), space = O(1)

class Solution {
public:
    long long minimumPossibleSum(int n, int target) 
    {
        int mid = (target >> 1) + 1;
        return (1ll * n * (n+1) >> 1ll) + 
            ((mid > n || target <= 2)? 0ll : 1ll * (target - mid) * (n - mid + 1));
    }
};
