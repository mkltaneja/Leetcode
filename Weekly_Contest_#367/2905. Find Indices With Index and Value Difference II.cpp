
// APPROACH 1 (Using set and finding lower_bound of every i + id indexed number) --> Time = O(n*logn), Space = O(n)

class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int id, int vd) 
    {
        int n = nums.size();
        set<pair<int,int>> st;
        for(int i = 0; i < n; i++)
        {
            if(i >= id)
                st.insert({nums[i-id], i-id});
            auto lb = st.lower_bound({nums[i] + vd, -1});
            if(lb != st.end())
                return {(*lb).second, i};
        }
        st.clear();
        for(int i = n-1; i >= 0; i--)
        {
            if(i + id < n)
                st.insert({nums[i+id], i+id});
            auto lb = st.lower_bound({nums[i] + vd, -1});
            if(lb != st.end())
                return {(*lb).second, i};
        }
        return {-1, -1};
    }
};

// APPROACH 2 (By Storing Maximum and minimum till i - id indexed numbers) --> Time = O(n), Space = O(1) [OPTIMIZED]

class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int id, int vd) 
    {
        int n = nums.size();
        int mni = 0, mxi = 0;
        for(int i = 0, j = i + id; j < n; i++, j++)
        {
            if(nums[i] < nums[mni])
                mni = i;
            if(nums[i] > nums[mxi])
                mxi = i;
            if(abs(nums[j] - nums[mni]) >= vd)
                return {mni, j};
            if(abs(nums[j] - nums[mxi]) >= vd)
                return {mxi, j};
        }
        
        return {-1, -1};
    }
};
