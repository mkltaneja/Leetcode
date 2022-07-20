
class Node
{
    Node left;
    Node right;
    int val;
    Node(int data)
    {
        this.left = null;
        this.right = null;
        this.val = data;
    }
};

int possible1 = 0;
Node insert(Node root, int data)
{
    if(root == null) 
    {
        possible1 = 1;
        return new Node(data);
    }

    if(root.val == data)
    {
        possible1 = 0;
        return root;
    }

    if(root.val < data)
        root.right = insert(root.right, data);
    else
        root.left = insert(root.left, data);

    return root;
}

int minVal(Node node)
{
    int mn = node.val;
    while(node.left)
    {
        node = node.left;
        mn = min(mn, node.val);
    }
    return mn;
}

int possibe2 = 0;
Node delete(Node root, int data)
{
    if(!root) 
    {
        possible2 = 0;
        return null;
    }

    if(root.val < data)
        root.right = delete(root.right, data);
    else 
        root.left = delete(root.left, data);

    else 
    {
        possible2 = 1;
        if(!root.left) return root.right;
        if(!root.right) return root.left;

        root.val = minVal(root.left);
        root.left = delete(root.left, root.val);
    }
    
    return root;
}

public int[] solve(int q, int[][] queries)
{
    Node root = null;
    int[] result = new int[n];
    for(int i = 0; i < q; i++)
    {
        if(queries[i][0] == 0)
        {
            possible1 = 0;
            insert(root, queries[i][1]);
            result[i] = possible2;
        }
        else 
        {
            possible2 = 0;
            delete(root, queries[i][1]);
            result[i] = possible2;
        }
    }

    return result;
}