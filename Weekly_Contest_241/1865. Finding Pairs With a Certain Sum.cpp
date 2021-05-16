class FindSumPairs
{
public:
    unordered_map<int, int> m;
    vector<int> v1, v2;
    FindSumPairs(vector<int> &nums1, vector<int> &nums2)
    {
        for (int x : nums2)
            m[x]++;
        v1 = nums1;
        v2 = nums2;
        sort(v1.begin(), v1.end());
    }

    void add(int index, int val)
    {
        m[v2[index]]--;
        v2[index] += val;
        m[v2[index]]++;
    }

    int count(int tot)
    {
        int ans = 0;
        for (int x : v1)
        {
            if (x >= tot)
                break;
            ans += m[tot - x];
        }
        return ans;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */