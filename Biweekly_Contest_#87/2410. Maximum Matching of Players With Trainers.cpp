class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) 
    {
        multiset<int> st;
        for(int x : trainers)
            st.insert(x);
        
        int ans = 0;
        for(int x : players)
        {
            auto ub = st.lower_bound(x);
            if(ub != st.end())
            {
                st.erase(ub);
                ans++;
            }
        }
        return ans;
    }
};
