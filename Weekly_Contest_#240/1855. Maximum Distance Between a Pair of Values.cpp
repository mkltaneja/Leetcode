
int maxDistance(vector<int> &nums1, vector<int> &nums2)
{
    int i = 0, j = 0, n = nums1.size(), m = nums2.size();
    int pvalid = 0, ans = 0;
    while (i < n && j < m)
    {
        if (nums1[i] > nums2[j])
        {
            if (i == j)
                i++, j++;
            else
                i++;
        }
        else
            while (j < m && nums2[j] >= nums1[i])
                j++;
        ans = max(ans, j - i - 1);
    }
    return ans;
}