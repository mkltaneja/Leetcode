void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    while (n || m)
        nums1[n + m] = (!n || (m && nums1[m - 1] >= nums2[n - 1])) ? nums1[--m] : nums2[--n];
}