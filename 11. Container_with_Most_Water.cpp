
int maxArea(vector<int> &height)
{
    int maxarea = 0;
    int i = 0, j = height.size() - 1;
    while (i < j)
    {
        maxarea = max(maxarea, (j - i) * min(height[i], height[j]));
        if (height[i] < height[j])
            i++;
        else
            j--;
    }
    return maxarea;
}