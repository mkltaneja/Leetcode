class Solution {
public:
    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) 
    {
        int n = nums1.size();
        long long ans = 0;
        vector<int> freq(n+1,0);
        
        int maj = 0, cnt = 0;
        for(int i = 0; i < n; i++)
        {
            freq[nums1[i]]++;
            freq[nums2[i]]++;
            if(nums1[i] == nums2[i])
            {
                ans += i;
                if(nums1[i] == maj || cnt == 0)
                {
                    maj = nums1[i];
                    cnt++;
                }
                else cnt--;
            }
        }
        
        for(int i = 0; i < n && cnt; i++)
        {
            if(nums1[i] != nums2[i] && nums1[i] != maj && nums2[i] != maj)
            {
                ans += i;
                cnt--;
            }
        }
        
        return freq[maj] > n? -1 : ans;
    }
};
