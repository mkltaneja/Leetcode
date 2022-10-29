class Solution {
public:
    
    #define f first
    #define s second
    vector<int> secondGreaterElement(vector<int>& nums) 
    {
        int n = nums.size();
        vector<pair<int,int>> vp(n);
        for(int i = 0; i < n; i++)
            vp[i] = {nums[i], i};
        sort(vp.begin(), vp.end(), [](auto &p1, auto &p2){
            return p1.f == p2.f? p1.s < p2.s : p1.f > p2.f;
        });
        
        set<int> st;
        vector<int> ans(n,-1);
        for(int i = 0; i < n; i++)
        {
            int x = vp[i].s;
            auto ub = st.upper_bound(x);
            if(ub != st.end())
            {
                ub++;
                if(ub != st.end()) ans[x] = nums[*ub];
            }
            
            st.insert(x);
        }
        
        return ans;
    }
};
