
Node *connect(Node *root)
{
    Node *node = root;
    Node *temp = node;
    while (node && node->left)
    {
        temp->left->next = temp->right;
        if (temp->next)
        {
            temp->right->next = temp->next->left;
            temp = temp->next;
        }
        else
        {
            node = node->left;
            temp = node;
        }
    }
    return root;
}