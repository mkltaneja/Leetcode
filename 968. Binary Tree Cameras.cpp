
int cameras = 0;
int bintreeCameras(TreeNode *node)
{
    if (!node)
        return 2;
    if (!node->left && !node->right)
        return 0;

    int lans = bintreeCameras(node->left);
    int rans = bintreeCameras(node->right);

    if (lans == 0 || rans == 0)
    {
        cameras++;
        return 1;
    }
    if (lans == 1 || rans == 1)
        return 2;

    return 0;
}

int minCameraCover(TreeNode *root)
{
    return (bintreeCameras(root) == 0) ? cameras + 1 : cameras;
}