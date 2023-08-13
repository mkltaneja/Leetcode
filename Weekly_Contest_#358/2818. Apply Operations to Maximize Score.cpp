class Solution {
public:
    
    int mod = 1e9 + 7;

    int prime_factors_count(int n) 
    {
        int count = 0;
        for (int i = 2; i * i <= n; ++i)
        {
            bool div = false;
            while (n % i == 0) 
            {
                n /= i;
                div = true;
            }
            if(div) count++;
        }
        if (n > 1)
            count++;
        return count;
    }

    vector<int> prime_score_array(vector<int> &arr)
    {
        vector<int> prime_scores;
        for (int num : arr) 
        {
            int prime_score = prime_factors_count(num);
            prime_scores.push_back(prime_score);
        }
        return prime_scores;
    }
    
    int binpowmod(long a, long b)
    {
        long ans = 1;
        while(b)
        {
            if(b & 1)
                ans = (ans % mod * a % mod) % mod;
            a = (a % mod * a % mod) % mod;
            b >>= 1;
        }
        return ans;
    }
    
    int maximumScore(vector<int>& nums, int k) 
    {
        int n = nums.size();
        
        vector<int> psa = prime_score_array(nums);
        vector<int> ng(n), pge(n);
        
        stack<int> st;
        for(int i = 0; i < n; i++)
        {
            while(!st.empty() && psa[st.top()] < psa[i])
            {
                ng[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty())
        {
            ng[st.top()] = n - st.top();
            st.pop();
        }
        for(int i = n-1; i >= 0; i--)
        {
            while(!st.empty() && psa[st.top()] <= psa[i])
            {
                pge[st.top()] = st.top() - i;
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty())
        {
            pge[st.top()] = st.top() + 1;
            st.pop();
        }
        
        vector<vector<long>> arr(n, vector<long>(3));
        for(int i = 0; i < n; i++)
            arr[i] = {nums[i], ng[i], pge[i]};
        sort(arr.rbegin(), arr.rend());
        
        long ans = 1;
        for(int i = 0; i < n; i++)
        {
            long subarrCnt = min(arr[i][1] * arr[i][2], (long)k);
            k -= subarrCnt;
            ans = (ans % mod * binpowmod(arr[i][0], subarrCnt) % mod) % mod;
        }
        
        return ans;
    }
};
